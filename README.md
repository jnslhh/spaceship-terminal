# Spaceship Terminal

A retro terminal spaceship animation in C++ using `ncursesw`. This project was ported from the original Python implementation to improve performance and allow packaging as an AUR package.

## Features
- Real-time parallax starfield rendering.
- Animated Unicode (Braille-art) spaceship.
- Responsive design that adapts dynamically to terminal resizing.
- Built using C++ and `ncursesw` for wide-character/Unicode terminal drawing.

## Prerequisites
To build and run this program, you will need:
- A C++ compiler supporting C++17 (`gcc` / `g++` or `clang++`).
- `make` build tool.
- `ncurses` development libraries with wide-character support (e.g., `libncursesw5-dev` on Debian/Ubuntu, or `ncurses` / `base-devel` on Arch Linux).

## Build Instructions

Compile the program using the provided `Makefile`:

```bash
make
```

This will produce the `spaceship` binary.

## Run Instructions

Run the compiled executable:

```bash
./spaceship
```

### Controls
- Press **q** to quit the animation.
- Resize the terminal window to see the layout dynamically adjust.

## AUR Package (Arch Linux)

This repository includes a basic `PKGBUILD` template for Arch Linux users who wish to publish or build this as an AUR package.

To build the package locally:
```bash
makepkg -si
```


