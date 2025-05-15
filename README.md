# rlText an enhaned text renderng systems for raylib
rlText is a library that contains an alternate font rendering system for raylib, that supports some new features not found in the core system

# Features
* Better support for HighDPI displays and automatic display scaling
* Allingment (left, right center)
* Text Wrapping
* Better handling of glpyh ranges
* Custom glyphs
* Inline color changes
* Kerning
* Flip Y for use with render textures
* Merge glyphs from other fonts
* Add glyph ranges as needed
* Atlas resizising

# Building
This library uses Game-premake from
https://github.com/raylib-extras/game-premake/

You can run the batch files on windows or premake5 gmake2 on other OSs to generate makefiles or visual studio proejcts. The library and it's examples are also setup for use in vscode, simply open the folder in vscode and run the build task.

# Example app
The example folder contains a simple use case of the library.

# Limitations
This library currently has some limitations
* TTF only, bitmap fonts are not supported
* Grayscale rendering only

# C++
The library does use C++ but does not use any complex classes or templates. Only basic C++ features such as references and containers are used.

# Color Codes
The font drawing system uses \a as an escape code for color, simply provide \a then a HTML color code
"Text \a#FF0000FFTHIS TEXT IS RED"
This will swap to the red color after "\a#FF0000FF". The color state will stay untill you change it back to a specific color. Text will default to the tint color.
You must specify all 4 components of the HTML color, including the alpha

# Todo
* Cache multiple sizes of glyph in the same atlas?
![image](https://raw.githubusercontent.com/JeffM2501/rlText/refs/heads/main/demo.gif)
