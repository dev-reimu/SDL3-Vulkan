# What is this project?
A robust and efficient SDL3 program that ties in with the Vulkan rendering API, written in the C language.

It aims to support multiple platforms and environments, while boasting a simple structure and being easy to understand.

---
# How does it work?
### Where does the program start?
The program starts in `initialize.c`, found in `/src/sdl/`, and follows [SDL](https://www.libsdl.org/)'s optional "Main Callbacks" structure (For details click on the following link and scroll down until you see "Main callbacks in SDL3": https://wiki.libsdl.org/SDL3/README-main-functions). This structure enables more control to the operating system over the runtime of the program.

### How are errors handled?
Throughout this project, you will encounter the function `SDL_*Reimu*_CheckError()`, which always forces the program to quit when an [SDL](https://www.libsdl.org/) error is detected. It can also log a custom error message of your choosing alongside it. If the program didn't fail however, the function is always followed by a success message of your choosing.

The function signed with my name has the purpose of abstracting error handling. Without it, you'd have to create an `if()` statement every single time you wanted to check for [SDL](https://www.libsdl.org/) errors. With it, you only waste two lines - 1 for the error check; 2 for the success message. In the commit history, there exist attempts to simplify this system to just one line, however, I can not figure out a way to combine strings with variables (like in the `printf()` function) and pass them as parameters to `SDL_Reimu_CheckError()`, so 2 lines will have to do for now. Tragic, I know.

---
# Building
### Windows
- Install a C/C++ compiler (Recommended: [GCC](https://winlibs.com/#download-release))
- [Download and install CMake](https://cmake.org/download/)
- Open a terminal in the project folder and run the provided build scripts, or make your own.
### MacOS
(Coming when I get a Mac or when someone else builds this project for it out of frustration because I couldn't bother to do it myself.)
### Linux
- Install a C/C++ compiler package (Recommended: `gcc`)
- Install CMake package (`cmake`)
- Open a terminal in the project folder and run the provided build scripts (`sh build.sh`, `sh run.sh`, `sh build-and-run.sh`), or make your own.
