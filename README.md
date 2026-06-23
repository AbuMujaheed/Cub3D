*This project has been created as part of the 42 curriculum by sojetimi, farmoham.*

# cub3D

## Description

`cub3D` is a small first-person 3D maze renderer inspired by classic raycasting
games such as Wolfenstein 3D. The goal of the project is to parse a `.cub`
configuration file, validate the map, load wall textures and colors, then render
a navigable scene using the MiniLibX graphics library.

The project focuses on:

- parsing and validating a custom map format;
- loading XPM textures for north, south, west, and east-facing walls;
- rendering walls, floor, and ceiling colors with a raycasting engine;
- handling player movement, rotation, and collision;
- managing resources and errors cleanly in C.

## Instructions

### Requirements

This project is built for Linux with MiniLibX. You need:

- `cc`
- `make`
- X11 development libraries
- Xext development libraries
- the math library, linked with `-lm`

On Debian/Ubuntu-based systems, the MiniLibX dependencies are usually available
with:

```sh
sudo apt install build-essential libx11-dev libxext-dev
```

### Compilation

From the root of the repository:

```sh
make
```

This builds the executable:

```sh
./cub3D
```

Useful Makefile rules:

```sh
make clean
make fclean
make re
```

### Execution

Run the program with one `.cub` map file:

```sh
./cub3D maps/example.cub
```

Other sample maps are available in the `maps/` directory.

### Controls

- `W` or `Up Arrow`: move forward
- `S` or `Down Arrow`: move backward
- `A`: strafe left
- `D`: strafe right
- `Left Arrow`: rotate left
- `Right Arrow`: rotate right
- `Esc` or window close button: quit

## Map Format

A `.cub` file contains texture paths, floor and ceiling colors, then the map
layout.

Example:

```text
NO textures/north.xpm
SO textures/south.xpm
WE textures/west.xpm
EA textures/east.xpm

F 40,40,45
C 120,170,210

111111111111
100000000001
100011100001
100010000001
1000100N0001
100000000001
111111111111
```

Map symbols:

- `1`: wall
- `0`: empty space
- `N`, `S`, `E`, `W`: player starting position and direction
- spaces: allowed only where the map remains properly closed

The map must be surrounded by walls and contain exactly one player start.

## Technical Choices

- Language: C
- Graphics: MiniLibX
- Rendering technique: raycasting with DDA grid traversal
- Textures: XPM files loaded through MiniLibX
- Utility library: local `libft`

The program uses a fixed-size window defined in `includes/cub3d.h`:

- width: `1024`
- height: `768`

## Resources

Classic references and useful background material:

- 42 cub3D subject and intra resources
- MiniLibX documentation and examples
- Lode Vandevenne's raycasting tutorial:
  <https://lodev.org/cgtutor/raycasting.html>
- Wolfenstein 3D raycasting explanations and articles
- Linux manual pages for file I/O, memory management, and X11-related behavior

AI usage:

- AI assistance was used to draft and polish `README.md`.
