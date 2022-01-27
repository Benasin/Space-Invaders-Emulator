# Space-Invaders-Emulator
Intel 8080 CPU emulator to play Space Invaders in C (SDL2 for graphics)

## Demo

![invaders](https://i.imgur.com/Unt11N0.gif)

## How to build and run

    gcc -o invaders cpu8080.c invaders.c -lSDL2
  
    ./invaders your_rom

## ROM
Because of copyright you should find the rom on the internet and combine it to 1 file

    cat invaders.h invaders.g invaders.f invaders.e > rom

## Controls
| Key | Function |
| - |--|
| C | Insert coins |
| 1 | P1 plays |
| 2 | P2 plays |
| Z | P1 move left |
| X | P1 move right |
| V | P1 shoots |
| N | P2 move left |
| M | P2 move right |
| Dot (.) | P2 shoots |

## Resources
https://computerarcheology.com/Arcade/SpaceInvaders

http://emulator101.com
