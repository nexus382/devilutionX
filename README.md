<p align="center">
<img width="554" src="https://user-images.githubusercontent.com/204594/113575181-c946a400-961d-11eb-8347-a8829fa3830c.png">
</p>

---

[![Discord Channel](https://img.shields.io/discord/518540764754608128?color=%237289DA&logo=discord&logoColor=%23FFFFFF)](https://discord.gg/devilutionx)
[![Downloads](https://img.shields.io/github/downloads/diasurgical/devilutionX/total.svg)](https://github.com/diasurgical/devilutionX/releases/latest)
[![Codecov](https://codecov.io/gh/diasurgical/devilutionX/branch/master/graph/badge.svg)](https://codecov.io/gh/diasurgical/devilutionX)

<p align="center">
<img width="838" src="https://github.com/user-attachments/assets/db6e94b1-a98b-413d-a109-1fb77dda34bd">
</p>

<sub>*(The health-bar and XP-bar are off by default but can be enabled in the [game settings](https://github.com/diasurgical/devilutionX/wiki/DevilutionX-diablo.ini-configuration-guide). Widescreen can also be disabled if preferred.)*</sub>

# What is DevilutionX

DevilutionX is a port of Diablo and Hellfire that strives to make it simple to run the game while providing engine improvements, bug fixes, and some optional quality of life features.

Check out the [manual](https://github.com/diasurgical/devilutionX/wiki) for available features and how to take advantage of them.

For a full list of changes, see our [changelog](docs/CHANGELOG.md).

# How to Install

Note: You'll need access to the data from the original game. If you don't have an original CD, you can [buy Diablo from GoG.com](https://www.gog.com/game/diablo) or Battle.net. Alternatively, you can use `spawn.mpq` from the [shareware](https://github.com/diasurgical/devilutionx-assets/releases/latest/download/spawn.mpq) [[2]](http://ftp.blizzard.com/pub/demos/diablosw.exe) version, in place of `DIABDAT.MPQ`, to play the shareware portion of the game.

Download the latest [DevilutionX release](https://github.com/diasurgical/devilutionX/releases/latest) and extract the contents to a location of your choosing or [build from source](#building-from-source).

- Copy `DIABDAT.MPQ` from the CD or Diablo installation (or [extract it from the GoG installer](https://github.com/diasurgical/devilutionX/wiki/Extracting-the-.MPQs-from-the-GoG-installer)) to the DevilutionX folder.
- To run the Diablo: Hellfire expansion, you will also need to copy `hellfire.mpq`, `hfmonk.mpq`, `hfmusic.mpq`, and `hfvoice.mpq`.

For more detailed instructions: [Installation Instructions](./docs/installing.md).

# Contributing

We are always looking for more people to help with [coding](docs/CONTRIBUTING.md), [documentation](https://github.com/diasurgical/devilutionX/wiki), [testing the latest builds](#test-builds), spreading the word, or simply just hanging out on our [Discord server](https://discord.gg/devilutionx).

# Mods

We hope to provide a good starting point for mods. In addition to the full Devilution source code, we also provide modding tools. Check out the list of known [mods based on DevilutionX](https://github.com/diasurgical/devilutionX/wiki/Mods-and-related-projects).

# Test Builds

If you want to help test the latest development version (make sure to back up your files, as these may contain bugs), you can fetch the test build artifact from one of the build servers:

*Note: You must be logged into GitHub to download the attachments!*

[![Linux x86_64](https://github.com/diasurgical/devilutionX/actions/workflows/Linux_x86_64.yml/badge.svg)](https://github.com/diasurgical/devilutionX/actions/workflows/Linux_x86_64.yml?query=branch%3Amaster)
[![Linux AArch64](https://github.com/diasurgical/devilutionX/actions/workflows/Linux_aarch64.yml/badge.svg)](https://github.com/diasurgical/devilutionX/actions/workflows/Linux_aarch64.yml?query=branch%3Amaster)
[![Linux x86](https://github.com/diasurgical/devilutionX/actions/workflows/Linux_x86.yml/badge.svg)](https://github.com/diasurgical/devilutionX/actions/workflows/Linux_x86.yml?query=branch%3Amaster)
[![Linux x86_64 SDL1](https://github.com/diasurgical/devilutionX/actions/workflows/Linux_x86_64_SDL1.yml/badge.svg)](https://github.com/diasurgical/devilutionX/actions/workflows/Linux_x86_64_SDL1.yml?query=branch%3Amaster)
[![macOS x86_64](https://github.com/diasurgical/devilutionX/actions/workflows/macOS_x86_64.yml/badge.svg)](https://github.com/diasurgical/devilutionX/actions/workflows/macOS_x86_64.yml?query=branch%3Amaster)
[![Windows MSVC x64](https://github.com/diasurgical/devilutionX/actions/workflows/Windows_MSVC_x64.yml/badge.svg)](https://github.com/diasurgical/devilutionX/actions/workflows/Windows_MSVC_x64.yml?query=branch%3Amaster)
[![Windows MinGW x64](https://github.com/diasurgical/devilutionX/actions/workflows/Windows_MinGW_x64.yml/badge.svg)](https://github.com/diasurgical/devilutionX/actions/workflows/Windows_MinGW_x64.yml?query=branch%3Amaster)
[![Windows MinGW x86](https://github.com/diasurgical/devilutionX/actions/workflows/Windows_MinGW_x86.yml/badge.svg)](https://github.com/diasurgical/devilutionX/actions/workflows/Windows_MinGW_x86.yml?query=branch%3Amaster)
[![Android](https://github.com/diasurgical/devilutionX/actions/workflows/Android.yml/badge.svg)](https://github.com/diasurgical/devilutionX/actions/workflows/Android.yml?query=branch%3Amaster)
[![iOS](https://github.com/diasurgical/devilutionX/actions/workflows/iOS.yml/badge.svg)](https://github.com/diasurgical/devilutionX/actions/workflows/iOS.yml?query=branch%3Amaster)
[![PS4](https://github.com/diasurgical/devilutionX/actions/workflows/PS4.yml/badge.svg)](https://github.com/diasurgical/devilutionX/actions/workflows/PS4.yml?query=branch%3Amaster)
[![Original Xbox](https://github.com/diasurgical/devilutionX/actions/workflows/xbox_nxdk.yml/badge.svg)](https://github.com/diasurgical/devilutionX/actions/workflows/xbox_nxdk.yml?query=branch%3Amaster)
[![Xbox One/Series](https://github.com/diasurgical/devilutionX/actions/workflows/xbox_one.yml/badge.svg)](https://github.com/diasurgical/devilutionX/actions/workflows/xbox_one.yml?query=branch%3Amaster)
[![Nintendo Switch](https://github.com/diasurgical/devilutionX/actions/workflows/switch.yml/badge.svg)](https://github.com/diasurgical/devilutionX/actions/workflows/switch.yml)
[![Sony PlayStation Vita](https://github.com/diasurgical/devilutionX/actions/workflows/vita.yml/badge.svg)](https://github.com/diasurgical/devilutionX/actions/workflows/vita.yml)
[![Nintendo 3DS](https://github.com/diasurgical/devilutionX/actions/workflows/3ds.yml/badge.svg)](https://github.com/diasurgical/devilutionX/actions/workflows/3ds.yml)
[![Amiga M68K](https://github.com/diasurgical/devilutionX/actions/workflows/amiga-m68k.yml/badge.svg)](https://github.com/diasurgical/devilutionX/actions/workflows/amiga-m68k.yml)

# Building from Source

Want to compile the program by yourself? Great! Simply follow the [build instructions](./docs/building.md).

# Credits

- The original Devilution project: [Devilution](https://github.com/diasurgical/devilution#credits)
- [Everyone](https://github.com/diasurgical/devilutionX/graphs/contributors) who worked on Devilution/DevilutionX
- [Nikolay Popov](https://www.instagram.com/nikolaypopovz/) for UI and graphics
- [WiAParker](https://wiaparker.pl/projekty/diablo-hellfire/) for the Polish voice pack
- And thanks to all who support the project, report bugs, and help spread the word ❤️

# Legal

DevilutionX is made publicly available and released under the Sustainable Use License (see [LICENSE](LICENSE.md)).

The source code in this repository is for non-commercial use only. If you use the source code, you may not charge others for access to it or any derivative work thereof.

Diablo® - Copyright © 1996 Blizzard Entertainment, Inc. All rights reserved. Diablo and Blizzard Entertainment are trademarks or registered trademarks of Blizzard Entertainment, Inc. in the U.S. and/or other countries.

DevilutionX and any of its maintainers are in no way associated with or endorsed by Blizzard Entertainment®.

# DevilutionX - Diablo for Dreamcast

DevilutionX is a source port of Diablo and Hellfire that strives to make it simple to run the game while providing engine improvements, bugfixes, and some optional quality of life features.

This is a fork designed for running the game on Dreamcast hardware.

Check the [changelog](docs/CHANGELOG.md) for what's been added since the last release.

<details><summary>Click to view the screenshots</summary>

![Screenshot 1](https://user-images.githubusercontent.com/204594/114579508-b6555d80-9c78-11eb-89dd-b51955792273.png)
![Screenshot 2](https://user-images.githubusercontent.com/204594/114579510-b6edf400-9c78-11eb-844d-2465f575a796.png)
![Screenshot 3](https://user-images.githubusercontent.com/204594/114579512-b6edf400-9c78-11eb-8632-bb975aae61c7.png)
![Screenshot 4](https://user-images.githubusercontent.com/204594/114579513-b7868a80-9c78-11eb-9322-8fa508fa8b41.png)
![Screenshot 5](https://user-images.githubusercontent.com/204594/114579515-b7868a80-9c78-11eb-87b8-218d3ff3c44d.png)
![Screenshot 6](https://user-images.githubusercontent.com/204594/114579517-b7868a80-9c78-11eb-89e4-7f03be1ace44.png)
![Screenshot 7](https://user-images.githubusercontent.com/204594/114579518-b81f2100-9c78-11eb-8c32-c46877b5ebaa.png)
![Screenshot 8](https://user-images.githubusercontent.com/204594/114579519-b81f2100-9c78-11eb-9cf1-8929e3fc191c.png)
![Screenshot 9](https://user-images.githubusercontent.com/204594/114579520-b81f2100-9c78-11eb-8aef-7a0bf7181961.png)
![Screenshot 10](https://user-images.githubusercontent.com/204594/114579522-b8b7b780-9c78-11eb-85da-ee117b9f5a7b.png)

</details>

## Installing

DevilutionX requires an MPQAPI.DLL, Storm.dll, standard.snp, and diabdat.mpq from the original game. A CD or GoG installation of Diablo is required.

You can follow the instructions in [debian.io's page on installing Diablo](https://archive.org/details/devilutionx-dc-test-files) which has the files you need.

## Dreamcast Features

### Memory Management
- Standard build supports 16MB RAM configuration
- With double memory mode enabled (Flycast with 32MB RAM mod), the game offers better performance

### Controls
- D-pad for movement
- Analog stick for cursor movement
- Dreamcast controller buttons for actions

### Audio Support
This version includes audio support for the Dreamcast port with the following optimizations:
- Mono audio (1 channel) with 22050Hz sample rate for reduced memory usage
- Sound files larger than 1KB are streamed from disc
- For best performance with 16MB RAM, convert audio files to ADPCM MS format using the included script

For setup details, see [Dreamcast Audio Documentation](docs/dreamcast_audio.md)

## Compiling

### Building with Docker

```bash
docker build -t devilutionx-dreamcast .
docker run --rm -v $(pwd):/work devilutionx-dreamcast
```

### Building with Native Tools

Make sure you have the KOS (KallistiOS) Dreamcast development environment set up.
See the [KallistiOS documentation](https://github.com/KallistiOS/KallistiOS) for installation instructions.

```bash
cmake -S. -Bbuild -DCMAKE_TOOLCHAIN_FILE=../KallistiOS/utils/cmake/dreamcast.toolchain.cmake
make -C build
```

For audio support, make sure to apply the KallistiOS modifications described in [the audio documentation](docs/dreamcast_audio.md).

## Contributing

DevilutionX is maintained by the DevilutionX team, and the Dreamcast port is maintained by azihassan. We welcome any contributions.

## F.A.Q

> Will you add cross-platform support?

The main branch already supports this, this fork is specifically for the Dreamcast port.

> What are the supported input devices?

Dreamcast Controller and potentially keyboard and mouse via the Dreamcast keyboard adapter.

> Will you support mods?

Not at this time, the Dreamcast has significant memory constraints.

## Credits

- The original Diablo game was created by Blizzard Entertainment
- DevilutionX is maintained by the DevilutionX Team
- The Dreamcast port is maintained by azihassan
- [diasurgical/devilutionX](https://github.com/diasurgical/devilutionX) team for the main port

## Legal

This software is being released to the Public Domain. No assets from the original game are included in this distribution.

You must own a copy of Diablo and have access to the game assets.

Battle.net® - Copyright © 1996 Blizzard Entertainment, Inc. All rights reserved. Battle.net and Blizzard Entertainment are trademarks or registered trademarks of Blizzard Entertainment, Inc. in the U.S. and/or other countries.

Diablo® - Copyright © 1996 Blizzard Entertainment, Inc. All rights reserved. Diablo and Blizzard Entertainment are trademarks or registered trademarks of Blizzard Entertainment, Inc. in the U.S. and/or other countries.

DevilutionX is not affiliated or endorsed by Blizzard or its parent company Activision Blizzard.

Activision Blizzard Inc. - Copyright © 2023 Activision Blizzard, Inc. All rights reserved.
