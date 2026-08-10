# Spaceship Terminal

A retro Unicode spaceship animation for the terminal, written in C++ with `ncursesw`.

## Features

- Animated Braille-art spaceship.
- Real-time parallax starfield.
- Responsive redraws when the terminal is resized.
- Small terminal guard that avoids invalid drawing coordinates.
- Single native binary with no runtime configuration required.

## Requirements

- C++17 compiler such as `g++` or `clang++`.
- `make`.
- `ncursesw` development libraries.

On Arch Linux, install the usual build tools and ncurses:

```bash
sudo pacman -S --needed base-devel ncurses
```

On Debian or Ubuntu:

```bash
sudo apt install build-essential libncursesw5-dev
```

## Build From Source

```bash
make
```

This creates the `spaceship` binary in the project directory.

## Run

```bash
./spaceship
```

## Install Locally

```bash
sudo make install PREFIX=/usr/local
```

To remove a local install:

```bash
sudo make uninstall PREFIX=/usr/local
```

## Controls

- Press `q` to exit.
- Resize the terminal window to redraw the scene.

## Arch Linux and AUR

This repository includes a `PKGBUILD` for the release package `spaceship-terminal`.

Build and install it locally with:

```bash
makepkg -si
```

The package installs the executable as:

```text
/usr/bin/spaceship
```

After changing `PKGBUILD` metadata, regenerate `.SRCINFO` before uploading to the AUR:

```bash
makepkg --printsrcinfo > .SRCINFO
```

For a final AUR release, replace the temporary `SKIP` checksum in `PKGBUILD` with the real SHA-256 checksum for the `v1.0.0` source archive after the tag exists.

## License

MIT
