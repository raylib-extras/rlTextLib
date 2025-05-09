# rlText an enhaned text renderng systems for raylib
rlText is a library that contains an alternate font rendering system for raylib, that supports some new features not found in the core system

# Features
* Better support for HighDPI displays and automatic display scaling
* Allingment (left, right center)
* Text Wrapping
* Better handling of glpyh ranges
* Custom glyphs
* Inline color changes

# Building
This library uses Game-premake from
https://github.com/raylib-extras/game-premake/

You can run the batch files on windows or premake5 gmake2 on other OSs to generate makefiles or visual studio proejcts. The library and it's examples are also setup for use in vscode, simply open the folder in vscode and run the build task.

# Example app
The example folder contains a simple use case of the library.

# C++
The library does use C++ but does not use any complex classes or templates. Only basic C++ features such as references and containers are used.