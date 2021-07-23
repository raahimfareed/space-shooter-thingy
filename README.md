# Space Shooter thingy - Budget Edition
Made with C++20 and SDL2

## Background
Something like Galaga and Space invaders but not really. Made this just to get the basics of SDL2

## Compiling
### Windows
Install
[Git Bash](https://git-scm.com/downloads), [Mingw64](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/8.1.0/threads-win32/seh/x86_64-8.1.0-release-win32-seh-rt_v6-rev0.7z/download), [SDL2](https://www.libsdl.org/download-2.0.php), [SDL_Image](https://www.libsdl.org/projects/SDL_image/), [SDL_TTF](https://www.libsdl.org/projects/SDL_ttf/), and [SDL_Mixer](https://www.libsdl.org/projects/SDL_mixer/).

### Linux
Install SDL2, SDL Image, SDL TTF and SDL Mixer.
#### For Arch
```bash
sudo pacman -S sdl2 sdl2_image sdl2_ttf sdl2_mixer
```
#### For other distros
```
Check your distro package manager/repos
```
### After acquiring SDL2

```bash
g++ -c src/*.cpp -std=c++20 -m64 -g -Wall -I include && g++ *.o -o bin/debug/main -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer
```
Compiled file will be located in `./bin/debug`, you will need to copy `./res` folder to `./bin/debug` folder. (On windows you will also need to copy SDL2 DLLs to `./bin/debug` folder)
### Credits
Used wav files from [PolyMarsDev Cursor Custodian](https://github.com/PolyMarsDev/Cursor-Custodian)
