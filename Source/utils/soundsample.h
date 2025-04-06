#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>

#include <Aulib/Stream.h>

#include "engine/sound_defs.hpp"
#include "utils/stdcompat/shared_ptr_array.hpp"

#ifdef __DREAMCAST__
#include <dc/sound/sound.h>
#endif

namespace devilution {

class SoundSample final {
public:
	SoundSample() = default;
	SoundSample(SoundSample &&) noexcept = default;
	SoundSample &operator=(SoundSample &&) noexcept = default;

	[[nodiscard]] bool IsLoaded() const
	{
#ifdef __DREAMCAST__
		return stream_ != nullptr || kosAdpcmStream_ != nullptr;
#else
		return stream_ != nullptr;
#endif
	}

	void Release();
	bool IsPlaying();

	// Returns 0 on success.
	int SetChunkStream(std::string filePath, bool isMp3, bool logErrors = true);

#ifdef __DREAMCAST__
	// KOS-specific functions for Yamaha ADPCM
	int SetKosADPCM(std::string filePath);
	int SetKosStreamingADPCM(std::string filePath);
#endif

	void SetFinishCallback(Aulib::Stream::Callback &&callback)
	{
		stream_->setFinishCallback(std::forward<Aulib::Stream::Callback>(callback));
	}

	/**
	 * @brief Sets the sample's WAV, FLAC, or Ogg/Vorbis data.
	 * @param fileData Buffer containing the data
	 * @param dwBytes Length of buffer
	 * @param isMp3 Whether the data is an MP3
	 * @return 0 on success, -1 otherwise
	 */
	int SetChunk(ArraySharedPtr<std::uint8_t> fileData, std::size_t dwBytes, bool isMp3);

	[[nodiscard]] bool IsStreaming() const
	{
#ifdef __DREAMCAST__
		// For ADPCM streams, check the type using file_path_ since that will always be set
		if (kosAdpcmStream_ && !file_path_.empty()) {
			// If using KOS streaming, just return true as we use the file path
			return true;
		}
#endif
		return file_data_ == nullptr;
	}

	int DuplicateFrom(const SoundSample &other)
	{
#ifdef __DREAMCAST__
		if (other.kosAdpcmStream_) {
			// Handle based on whether it's streaming or not
			if (other.IsStreaming()) {
				return SetKosStreamingADPCM(other.file_path_);
			} else {
				return SetKosADPCM(other.file_path_);
			}
		}
#endif
		if (other.IsStreaming())
			return SetChunkStream(other.file_path_, other.isMp3_);
		return SetChunk(other.file_data_, other.file_data_size_, other.isMp3_);
	}

	/**
	 * @brief Start playing the sound for a given number of iterations (0 means loop).
	 */
	bool Play(int numIterations = 1);

	/**
	 * @brief Start playing the sound with the given sound and user volume, and a stereo position.
	 */
	bool PlayWithVolumeAndPan(int logSoundVolume, int logUserVolume, int logPan)
	{
		SetVolume(logSoundVolume + logUserVolume * (ATTENUATION_MIN / VOLUME_MIN), ATTENUATION_MIN, 0);
		SetStereoPosition(logPan);
		return Play();
	}

	/**
	 * @brief Stop playing the sound
	 */
	void Stop()
	{
#ifdef __DREAMCAST__
		if (kosAdpcmStream_) {
			kosAdpcmStream_->stop();
			return;
		}
#endif
		stream_->stop();
	}

	void SetVolume(int logVolume, int logMin, int logMax);
	void SetStereoPosition(int logPan);

	void Mute()
	{
#ifdef __DREAMCAST__
		if (kosAdpcmStream_) {
			kosAdpcmStream_->mute();
			return;
		}
#endif
		stream_->mute();
	}

	void Unmute()
	{
#ifdef __DREAMCAST__
		if (kosAdpcmStream_) {
			kosAdpcmStream_->unmute();
			return;
		}
#endif
		stream_->unmute();
	}

	/**
	 * @return Audio duration in ms
	 */
	int GetLength() const;

private:
	// Non-streaming audio fields:
	ArraySharedPtr<std::uint8_t> file_data_;
	std::size_t file_data_size_;

	// Set for streaming audio to allow for duplicating it:
	std::string file_path_;

	bool isMp3_;

	std::unique_ptr<Aulib::Stream> stream_;
	
#ifdef __DREAMCAST__
	// For KOS Yamaha ADPCM support
	class KosADPCMStream;
	std::unique_ptr<KosADPCMStream> kosAdpcmStream_;
#endif
};

} // namespace devilution
