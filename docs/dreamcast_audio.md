# Dreamcast Audio Implementation Guide

This document explains how to enable audio support on the Dreamcast port of DevilutionX.

## Required KallistiOS Modifications

For audio to work properly on Dreamcast, you need to make two changes to your KallistiOS build:

### 1. Fix the Operator Names Issue

The SDL_audiolib library uses C++ keywords like `and`, `or`, and `not` which are incompatible with KallistiOS's default compilation flags. There are two ways to fix this:

#### Option A: Update KallistiOS (recommended)
Apply the fix from [KallistiOS/KallistiOS#785](https://github.com/KallistiOS/KallistiOS/pull/785) which removes the `-fno-operator-names` flag.

#### Option B: Patch SDL_audiolib
If you can't update KallistiOS, you can modify SDL_audiolib source files with the following commands:
```
find /path/to/build/_deps/sdl_audiolib-src/ -name '*.h' -or -name '*.cpp' | xargs sed -i 's/\bnot\b/!/g'
find /path/to/build/_deps/sdl_audiolib-src/ -name '*.h' -or -name '*.cpp' | xargs sed -i 's/\bor\b/\|\|/g'
find /path/to/build/_deps/sdl_audiolib-src/ -name '*.h' -or -name '*.cpp' | xargs sed -i 's/\band\b/\&\&/g'
```

### 2. Increase Thread Stack Size

The default thread stack size in KallistiOS is too small for DevilutionX audio. You need to increase it by editing:
`kos/kernel/arch/dreamcast/include/arch/arch.h`

Change:
```c
#define THD_KERNEL_STACK_SIZE (32 * 1024)
```
To:
```c
#define THD_KERNEL_STACK_SIZE (64 * 1024)
```

Or, if using a newer KallistiOS that supports overriding this value, you can define it in your build environment:
```
export THD_KERNEL_STACK_SIZE=65536
```

### 3. Increase File Handle Limits

To prevent "file not found" errors when loading many audio files, increase these values in `kos/include/kos/opts.h`:

```c
#define FS_CD_MAX_FILES 4096
#define FD_SETSIZE 4096
```

## Audio Optimization Strategies

To make audio work within the Dreamcast's limited memory:

1. **Reduce Quality**: The Dreamcast build uses mono audio (1 channel) with a 22050Hz sample rate
   
2. **Stream Large Files**: Audio files larger than 1KB are streamed from disc

3. **Convert Audio Files**:
   - For better memory usage, convert WAV files to compressed formats
   - MP3 works well if KallistiOS is built with MP3 support
   - ADPCM_MS format can be used as well:
     ```
     ffmpeg -y -i source.wav -acodec adpcm_ms output.wav
     ```

4. **Memory Usage**:
   - With 32MB RAM mode (Flycast emulator setting), audio works out of the box
   - With standard 16MB RAM, careful memory management is needed

## Known Issues

- Some sound effects may be choppy or have echo
- Sound and game actions may have a slight delay with larger buffer sizes
- Loading the town level requires about 6-7MB of audio data

## Troubleshooting

If you experience crashes:
1. Check if they occur with specific audio files
2. Try increasing audio buffer size
3. Ensure you have the latest KallistiOS with all the fixes mentioned above 