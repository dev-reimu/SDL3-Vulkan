# What is this project?
A robust and efficient SDL3 program that ties in with the Vulkan rendering API, written in the C language.

It aims to support multiple platforms and environments, while boasting a simple structure and being easy to understand.

---
# How does it work?
### Where does the program start?
The program starts in `initialize.c`, found in `/src/sdl/`. This program follows [SDL](https://www.libsdl.org/)'s optional "Main Callbacks" system (Scroll down until you see "Main callbacks in SDL3": https://wiki.libsdl.org/SDL3/README-main-functions). This structure enables more control to the operating system over the runtime of the program.

### How are errors handled?
Throughout this project, you will encounter the function `SDL_*Reimu*_CheckError()`, which always forces the program quit when an [SDL](https://www.libsdl.org/) error is detected. It can also log a custom error message of your choosing alongside it. In the case that the program didn't fail, the function is always followed by success message of your choosing. The function signed with my name has the purpose of abstracting error handling. Without it, you'd have to create an `if()` statement every single time you wanted to check for [SDL](https://www.libsdl.org/) errors. With it, you only waste two lines - 1 for the error check; 2 for the success message. In the commit history, there exist attempts to simplify this system to just one line, however, I can not figure out a way to combine strings with variables (like in the `printf()` function) and pass them as parameters to `SDL_Reimu_CheckError()`, so 2 lines will have to do for now. Tragic, I know.

---
# Building
### Windows
(Coming soon)
### MacOS
(Coming soon)
### Linux
Packages required:
`gcc cmake`
