# What is this project?
A robust and efficient SDL3 program that ties in with the Vulkan rendering API, written in the C language.

It aims to support multiple platforms and environments, while boasting a simple structure and being easy to understand.

---
# How does it work?
The program starts with the file `initialize.c`, found in `/src/sdl/`. To understand its significance, as well as that of the other files found in that folder, open the following link and scroll down until you see "Main callbacks in SDL3": https://wiki.libsdl.org/SDL3/README-main-functions. To put it simply, this program follows an optional structure provided by the [SDL](https://www.libsdl.org/) project. This structure enables more control to the operating system.

Throughout the project, you will encounter the function `SDL_*Reimu*_CheckError()`, which always forces the program quit when an SDL error is detected. It can also log a custom error message of your choosing. This is always followed by an `SDL_Log()` function call showing a successful message. The function signed with my name has the purpose of abstracting error handling. Without it, you'd have to create an `if()` statement every single time you wanted to check for [SDL](https://www.libsdl.org/) errors. With it, you only waste two lines - 1 for the custom function; 2 for the standard log. At some points in the commit history, there exist attempts to simplify error/success handling to just one line, however C is a vile beast, and dynamic allocation is something beyond me at this point, so 2 lines will have to do for now. Tragic, I know.

---
# Building
### Windows
(Coming soon)
### MacOS
(Coming soon)
### Linux
Packages required:
`gcc cmake`
