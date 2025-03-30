/**
 * @file audio.h
 *
 * Interface of Dreamcast-specific audio optimizations.
 */
#pragma once

#include <cstddef>
#include <string>
#include "engine/sound.h"

// Forward declarations to reduce header dependencies
struct SDL_RWops;

namespace devilution {

/**
 * @brief Checks if a sound effect is considered critical and should always be preloaded
 * @param path Path to the sound file
 * @return true if this is a critical sound effect, false otherwise
 */
bool IsCriticalSoundEffect(const char* path);

/**
 * @brief Determines if a sound file should be streamed from disc
 * @param path Path to the sound file
 * @param size Size of the sound file
 * @return true if the file should be streamed, false if it should be preloaded
 */
bool ShouldStreamAudio(const char* path, size_t size);

/**
 * @brief Logs the memory usage of an audio file
 * @param path Path to the sound file
 * @param size Size of the sound file
 * @param isStreaming Whether the file is being streamed
 */
void LogAudioMemoryUsage(const char* path, size_t size, bool isStreaming);

/**
 * @brief Logs the total memory usage of all loaded audio files
 */
void LogTotalAudioMemoryUsage();

/**
 * @brief Loads a sound effect with Dreamcast-specific optimizations
 * @param sound Sound structure to load into
 * @param path Path to the sound file
 * @return true if successful, false otherwise
 */
bool LoadSoundEffectForDreamcast(TSnd* sound, const char* path);

/**
 * @brief Performs memory optimization for audio on Dreamcast
 */
void OptimizeAudioMemoryUsage();

/**
 * @brief Initializes Dreamcast audio optimizations
 */
void InitDreamcastAudio();

} // namespace devilution 