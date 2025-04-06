#include "utils/soundsample.h"

#include <chrono>
#include <cmath>
#include <cstdint>
#include <utility>

#include <Aulib/DecoderDrmp3.h>
#include <Aulib/DecoderDrwav.h>
#include <SDL.h>
#ifdef USE_SDL1
#include "utils/sdl2_to_1_2_backports.h"
#else
#include "utils/sdl2_backports.h"
#endif

#include "engine/assets.hpp"
#include "options.h"
#include "utils/aulib.hpp"
#include "utils/log.hpp"
#include "utils/math.h"
#include "utils/stubs.h"

#ifdef __DREAMCAST__
#include <kos.h>
#include <dc/sound/sound.h>
#include <dc/sound/stream.h>
#include "memory_stats.h"
#endif

namespace devilution {

namespace {

constexpr float LogBase = 10.0;

/**
 * Scaling factor for attenuating volume.
 * Picked so that a volume change of -10 dB results in half perceived loudness.
 * VolumeScale = -1000 / log(0.5)
 */
constexpr float VolumeScale = 3321.9281F;

/**
 * Min and max volume range, in millibel.
 * -100 dB (muted) to 0 dB (max. loudness).
 */
constexpr float MillibelMin = -10000.F;
constexpr float MillibelMax = 0.F;

/**
 * Stereo separation factor for left/right speaker panning. Lower values increase separation, moving
 * sounds further left/right, while higher values will pull sounds more towards the middle, reducing separation.
 * Current value is tuned to have ~2:1 mix for sounds that happen on the edge of a 640x480 screen.
 */
constexpr float StereoSeparation = 6000.F;

float PanLogToLinear(int logPan)
{
	if (logPan == 0)
		return 0;

	auto factor = std::pow(LogBase, static_cast<float>(-std::abs(logPan)) / StereoSeparation);

	return copysign(1.F - factor, static_cast<float>(logPan));
}

std::unique_ptr<Aulib::Decoder> CreateDecoder(bool isMp3)
{
	if (isMp3)
		return std::make_unique<Aulib::DecoderDrmp3>();
	return std::make_unique<Aulib::DecoderDrwav>();
}

std::unique_ptr<Aulib::Stream> CreateStream(SDL_RWops *handle, bool isMp3)
{
	auto decoder = CreateDecoder(isMp3);
	if (!decoder->open(handle)) // open for `getRate`
		return nullptr;
	auto resampler = CreateAulibResampler(decoder->getRate());
	return std::make_unique<Aulib::Stream>(handle, std::move(decoder), std::move(resampler), /*closeRw=*/true);
}

/**
 * @brief Converts log volume passed in into linear volume.
 * @param logVolume Logarithmic volume in the range [logMin..logMax]
 * @param logMin Volume range minimum (usually ATTENUATION_MIN for game sounds and VOLUME_MIN for volume sliders)
 * @param logMax Volume range maximum (usually 0)
 * @return Linear volume in the range [0..1]
 */
float VolumeLogToLinear(int logVolume, int logMin, int logMax)
{
	const auto logScaled = math::Remap(static_cast<float>(logMin), static_cast<float>(logMax), MillibelMin, MillibelMax, static_cast<float>(logVolume));
	return std::pow(LogBase, logScaled / VolumeScale); // linVolume
}

} // namespace

#ifdef __DREAMCAST__
// Custom stream implementation for Dreamcast Yamaha ADPCM
class KosADPCMStream {
public:
	KosADPCMStream() : 
		isPlaying_(false),
		isStream_(false),
		soundHandle_(-1) {}

	~KosADPCMStream() {
		stop();
	}

	bool play(int numIterations) {
		if (soundHandle_ < 0)
			return false;

		isPlaying_ = true;
		if (isStream_) {
			// For streaming audio
			snd_stream_start(soundHandle_, numIterations == 0 ? SND_STREAM_LOOP : SND_STREAM_ONCE);
		} else {
			// For sound effects
			snd_sfx_play(soundHandle_, numIterations == 0 ? 255 : 254, 0);
		}
		return true;
	}

	void stop() {
		if (soundHandle_ >= 0) {
			if (isStream_) {
				snd_stream_stop(soundHandle_);
				snd_stream_destroy(soundHandle_);
			} else {
				snd_sfx_stop(soundHandle_);
				snd_sfx_unload(soundHandle_);
			}
			soundHandle_ = -1;
		}
		isPlaying_ = false;
	}

	bool isPlaying() const {
		return isPlaying_;
	}

	void setVolume(float volume) {
		if (soundHandle_ >= 0) {
			// Convert 0-1 float to 0-255 int
			int vol = static_cast<int>(volume * 255.0f);
			if (isStream_) {
				snd_stream_volume(soundHandle_, vol);
			} else {
				// For SFX, we'd need to store the pan and apply both
				// Not directly supported by KOS API
			}
		}
	}

	void setStereoPosition(float pan) {
		// Stereo pan not directly supported by KOS
		// Would need custom implementation
	}

	void mute() {
		if (soundHandle_ >= 0) {
			if (isStream_) {
				snd_stream_volume(soundHandle_, 0);
			}
		}
	}

	void unmute() {
		// Would need to restore previous volume
	}

	bool isMuted() const {
		// Would need to track mute state
		return false;
	}

	// Initialize as streaming ADPCM
	bool initStreamingADPCM(const char* filePath) {
		isStream_ = true;
		
		// Open ADPCM stream file
		soundHandle_ = snd_stream_load(filePath);
		if (soundHandle_ < 0) {
			LogError(LogCategory::Audio, "Failed to load ADPCM stream: {}", filePath);
			return false;
		}
		
		Log(LogCategory::Audio, "Loaded ADPCM stream: {} (handle: {})", filePath, soundHandle_);
		return true;
	}

	// Initialize as SFX ADPCM
	bool initADPCMSfx(const char* filePath) {
		isStream_ = false;
		
		// Load SFX from file
		soundHandle_ = snd_sfx_load(filePath);
		if (soundHandle_ < 0) {
			LogError(LogCategory::Audio, "Failed to load ADPCM SFX: {}", filePath);
			return false;
		}
		
		Log(LogCategory::Audio, "Loaded ADPCM SFX: {} (handle: {})", filePath, soundHandle_);
		return true;
	}

private:
	bool isPlaying_;
	bool isStream_;
	int soundHandle_; // KOS sound handle
};
#endif

///// SoundSample /////

void SoundSample::Release()
{
	stream_ = nullptr;
	file_data_ = nullptr;
	file_data_size_ = 0;
#ifdef __DREAMCAST__
	if (kosAdpcmStream_) {
		kosAdpcmStream_ = nullptr;
	}
#endif
}

/**
 * @brief Check if a the sound is being played atm
 */
bool SoundSample::IsPlaying()
{
#ifdef __DREAMCAST__
	if (kosAdpcmStream_) {
		return kosAdpcmStream_->isPlaying();
	}
#endif
	return stream_ && stream_->isPlaying();
}

bool SoundSample::Play(int numIterations)
{
#ifdef __DREAMCAST__
	if (kosAdpcmStream_) {
		return kosAdpcmStream_->play(numIterations);
	}
#endif

	if (!stream_->play(numIterations)) {
		LogError(LogCategory::Audio, "Aulib::Stream::play (from SoundSample::Play): {}", SDL_GetError());
		return false;
	}
	return true;
}

#ifdef __DREAMCAST__
int SoundSample::SetKosADPCM(std::string filePath)
{
	// Release any existing resources
	Release();
	
	// Create new KOS ADPCM stream handler
	kosAdpcmStream_ = std::make_unique<KosADPCMStream>();
	
	// Initialize as non-streaming SFX
	if (!kosAdpcmStream_->initADPCMSfx(filePath.c_str())) {
		kosAdpcmStream_ = nullptr;
		return -1;
	}
	
	file_path_ = std::move(filePath);
	isMp3_ = false;  // Not an MP3
	
	return 0;
}

int SoundSample::SetKosStreamingADPCM(std::string filePath)
{
	// Release any existing resources
	Release();
	
	// Create new KOS ADPCM stream handler
	kosAdpcmStream_ = std::make_unique<KosADPCMStream>();
	
	// Initialize as streaming audio
	if (!kosAdpcmStream_->initStreamingADPCM(filePath.c_str())) {
		kosAdpcmStream_ = nullptr;
		return -1;
	}
	
	file_path_ = std::move(filePath);
	isMp3_ = false;  // Not an MP3
	
	return 0;
}
#endif

int SoundSample::SetChunkStream(std::string filePath, bool isMp3, bool logErrors)
{
	SDL_RWops *handle = OpenAssetAsSdlRwOps(filePath.c_str(), /*threadsafe=*/true);
	if (handle == nullptr) {
		if (logErrors)
			LogError(LogCategory::Audio, "OpenAsset failed (from SoundSample::SetChunkStream) for {}: {}", filePath, SDL_GetError());
		return -1;
	}
	file_path_ = std::move(filePath);
	isMp3_ = isMp3;
	stream_ = CreateStream(handle, isMp3);
	if (!stream_->open()) {
		stream_ = nullptr;
		if (logErrors)
			LogError(LogCategory::Audio, "Aulib::Stream::open (from SoundSample::SetChunkStream) for {}: {}", file_path_, SDL_GetError());
		return -1;
	}
	return 0;
}

int SoundSample::SetChunk(ArraySharedPtr<std::uint8_t> fileData, std::size_t dwBytes, bool isMp3)
{
	isMp3_ = isMp3;
	file_data_ = std::move(fileData);
	file_data_size_ = dwBytes;
	SDL_RWops *buf = SDL_RWFromConstMem(file_data_.get(), static_cast<int>(dwBytes));
	if (buf == nullptr) {
		return -1;
	}

	stream_ = CreateStream(buf, isMp3_);
	if (!stream_->open()) {
		stream_ = nullptr;
		file_data_ = nullptr;
		LogError(LogCategory::Audio, "Aulib::Stream::open (from SoundSample::SetChunk): {}", SDL_GetError());
		return -1;
	}

	return 0;
}

void SoundSample::SetVolume(int logVolume, int logMin, int logMax)
{
#ifdef __DREAMCAST__
	if (kosAdpcmStream_) {
		float linearVolume = VolumeLogToLinear(logVolume, logMin, logMax);
		kosAdpcmStream_->setVolume(linearVolume);
		return;
	}
#endif
	stream_->setVolume(VolumeLogToLinear(logVolume, logMin, logMax));
}

void SoundSample::SetStereoPosition(int logPan)
{
#ifdef __DREAMCAST__
	if (kosAdpcmStream_) {
		float linearPan = PanLogToLinear(logPan);
		kosAdpcmStream_->setStereoPosition(linearPan);
		return;
	}
#endif
	stream_->setStereoPosition(PanLogToLinear(logPan));
}

int SoundSample::GetLength() const
{
#ifdef __DREAMCAST__
	if (kosAdpcmStream_) {
		// KOS doesn't provide an easy way to get length
		// Return a default value or 0
		return 0;
	}
#endif
	if (!stream_)
		return 0;
	return static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(stream_->duration()).count());
}

} // namespace devilution
