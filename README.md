# GenesisV - OpenGL Learning Project

This is a simple project to learn OpenGL from scratch. It has several examples that go from the most basic stuff to more complicated things.

## What is this?

GenesisV is a collection of OpenGL examples written in C++. Each example shows something different and they gradually increase in difficulty. The first one is just a rotating triangle, and the last ones have textures and more advanced effects.

## What do I need?

- Windows (because it uses Windows OpenGL libraries)
- MinGW installed (to compile with g++)
- A bit of patience if you've never compiled C++ before

## How do I compile it?

The easiest way is to use the compilation menu. Open a terminal in the GenesisV folder and run:

```
compilar_menu.bat
```

A menu will appear with all the examples. Just pick the number of the one you want to see and that's it. The program will compile and run automatically.

If you prefer to compile manually, there are instructions in the COMPILAR.md and COMPILAR_CON_MINGW.md files.

## What examples are there?

There are 15 examples plus a base one:

**Basic examples (001-005):**
- 001: A simple rotating triangle
- 002: A square with colors
- 003: A cube made only with lines (wireframe)
- 004: A solid cube with colors
- 005: Multiple objects rotating at once

**Texture examples (006-015):**
- 006: A square with wood texture
- 007: A cube with texture
- 008: Cube with different textures on each face
- 009: Moving texture (animated)
- 010: Different texture filtering types
- 011: Using tiles from a large image
- 012: Multiple objects with different textures
- 013: Textures with lighting
- 014: More complex scene with several things
- 015: Advanced texture effects

The base example (GenesisV.cpp) is a rotating pyramid.

## Controls

In all examples they work the same:
- **ESC**: Exit
- **F1**: Fullscreen / Window

Some examples have extra controls, like 010 which has a key to change the filter.

## Project structure

- `GenesisCORE.h` and `GenesisCORE.cpp`: The code that handles the window and OpenGL. You don't need to touch it.
- `GenesisV.cpp`: The base example
- `GenesisV-001.cpp` through `GenesisV-015.cpp`: The examples
- `TextureLoader.h` and `TextureLoader.cpp`: Code to load textures (JPG and BMP)
- `images/`: Folder with the textures used by the examples
- `compilar_menu.bat`: The script to compile easily

## Where do I start?

If you've never used OpenGL, start with 001 and go in order. Each example explains new concepts. If you already know something, you can jump to the ones that interest you.

## Notes

- All examples are well commented
- The code is simple and easy to understand
- You can modify any example to experiment
- Textures must be in the `images` folder next to the executable

## Common problems

If it doesn't compile:
- Check that MinGW is installed and in the PATH
- Make sure you're in the GenesisV folder when running the script

If textures don't load:
- Check that the `images` folder is in the same place as the .exe
- Files must be JPG or BMP

## License

This is an educational project. Use it however you want to learn.
