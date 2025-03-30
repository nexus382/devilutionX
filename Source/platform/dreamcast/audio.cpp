/**
 * @file audio.cpp
 *
 * Dreamcast-specific audio optimizations and memory management.
 */
#include "platform/dreamcast/audio.h"

#include <SDL.h>
#include <algorithm>
#include <cstdint>
#include <cstring>
#include <string>
#include <unordered_map>
#include <vector>

#include "effects.h"
#include "engine/assets.hpp"
#include "engine/sound.h"
#include "utils/log.hpp"

#ifdef __DREAMCAST__
#include <kos.h>
#endif

namespace devilution {

namespace {

// Track memory usage for audio files
size_t gTotalAudioMemoryUsage = 0;
std::unordered_map<std::string, size_t> gAudioFileSizes;

// Critical sound effects that should always be preloaded
// These are small, frequently used sounds that should never be streamed
const char* criticalSfx[] = {
    "sfx\\misc\\walk.wav",    // Walking sound
    "sfx\\misc\\cast.wav",    // Spell casting
    "sfx\\misc\\swing.wav",   // Weapon swing
    "sfx\\misc\\tmag.wav",    // Town portal
    "sfx\\misc\\healing.wav", // Healing potion
    "sfx\\misc\\mana.wav",    // Mana potion
    "sfx\\misc\\drop.wav",    // Item drop
    "sfx\\misc\\gold.wav",    // Gold drop
    "sfx\\misc\\invlght.wav", // Inventory light
    "sfx\\items\\flipswrd.wav", // Weapon equip
    "sfx\\misc\\lever.wav",   // Lever activation
    "sfx\\misc\\chest.wav",   // Open chest
    "sfx\\misc\\door.wav",    // Open door
    "sfx\\misc\\attack.wav",  // Attack
    "sfx\\misc\\dead.wav",    // Monster death
    "sfx\\misc\\bfire.wav",   // Fire spell
    "sfx\\misc\\bldstar.wav", // Blood star spell
    "sfx\\misc\\teleport.wav" // Teleport
};

} // namespace

bool IsCriticalSoundEffect(const char* path)
{
    if (path == nullptr) {
        return false;
    }
    
    // Check if the sound effect is in our critical list
    for (const char* sfx : criticalSfx) {
        if (SDL_strcasecmp(path, sfx) == 0) {
            return true;
        }
    }
    return false;
}

bool ShouldStreamAudio(const char* path, size_t size)
{
    if (path == nullptr) {
        return true; // Default to streaming if path is invalid
    }
    
    // Always stream music files
    if (SDL_strstr(path, "music\\") != nullptr || SDL_strstr(path, "music/") != nullptr) {
        return true;
    }
    
    // Never stream critical sound effects
    if (IsCriticalSoundEffect(path)) {
        return false;
    }
    
    // Check if we have a size threshold defined
#ifdef STREAM_ALL_AUDIO_MIN_FILE_SIZE
    // Stream files larger than the threshold
    return size >= STREAM_ALL_AUDIO_MIN_FILE_SIZE;
#else
    // Default to streaming files larger than 2KB if no threshold defined
    return size >= 2048;
#endif
}

void LogAudioMemoryUsage(const char* path, size_t size, bool isStreaming)
{
    if (path == nullptr) {
        return;
    }
    
    gAudioFileSizes[path] = size;
    
    if (!isStreaming) {
        gTotalAudioMemoryUsage += size;
    }
    
    LogVerbose(LogCategory::Audio, "{} - Size: {}KB, Streaming: {}, Total Memory: {}KB", 
        path, size / 1024, isStreaming ? "Yes" : "No", gTotalAudioMemoryUsage / 1024);
}

void LogTotalAudioMemoryUsage()
{
    LogVerbose(LogCategory::Audio, "Total Audio Memory Usage: {}KB", gTotalAudioMemoryUsage / 1024);
}

bool LoadSoundEffectForDreamcast(TSnd* sound, const char* path)
{
    if (sound == nullptr || path == nullptr) {
        return false;
    }
    
    AssetRef ref = FindAsset(path);
    if (!ref.ok()) {
        return false;
    }
    
    size_t size = ref.size();
    bool shouldStream = ShouldStreamAudio(path, size);
    
    // Log memory usage for tracking
    LogAudioMemoryUsage(path, size, shouldStream);
    
    // The actual loading is done by the engine's sound_file_load function
    // We just provide guidance on whether to stream or not
    return true;
}

void OptimizeAudioMemoryUsage()
{
#ifdef __DREAMCAST__
    // Check if we need to free some memory - Dreamcast has limited RAM
    if (gTotalAudioMemoryUsage > 6 * 1024 * 1024) { // Over 6MB of audio
        LogVerbose(LogCategory::Audio, "WARNING: Audio memory usage is high ({}KB)", 
            gTotalAudioMemoryUsage / 1024);
    }

    // Log available memory
    size_t freemem = 0;
    size_t total = 0;
    float percent = 0;
    
    // Attempt to get memory info, but don't crash if it fails
    #ifdef KOS_MEM_REAL
    kos_get_free_memory(&freemem, &total, &percent);
    LogVerbose(LogCategory::Audio, "Free memory: {}KB / {}KB ({}%)", 
        freemem / 1024, total / 1024, (int)(percent * 100));
    #endif
#endif
}

void InitDreamcastAudio()
{
    LogVerbose(LogCategory::Audio, "Initializing Dreamcast audio optimizations");
    gTotalAudioMemoryUsage = 0;
    gAudioFileSizes.clear();
}

} // namespace devilution
 