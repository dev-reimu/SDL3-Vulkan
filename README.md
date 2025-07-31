# What is this project?
A robust and efficient SDL3 program that ties in with the Vulkan rendering API, written in the C language.

It aims to support multiple platforms and environments, while boasting a simple structure and being easy to understand.

---
# How does it work?
### Where does the program start?
The program starts with the file `initialize.c`, found in `/src/sdl/`. To understand its significance, as well as that of the other files found in that folder, open the following link and scroll down until you see "Main callbacks in SDL3": https://wiki.libsdl.org/SDL3/README-main-functions. To put it simply, this program follows an optional structure provided by the [SDL](https://www.libsdl.org/) project. This structure enables more control to the operating system.

### How are errors handled?
Throughout the project, you will encounter the function `SDL_*Reimu*_CheckError()`, with an error message in the parentheses, followed by a standard `SDL_Log()` function showing a successful message. The function signed with my name has the purpose of abstracting error handling. Without it, you'd have to create an `if()` statement every single time you wanted to check for [SDL](https://www.libsdl.org/) errors. With it, you only waste two lines - 1 for the custom function; 2 for the standard log. At some points in the commit history, there exist attempts to simplify error/success handling to just one line, however, I can not figure out a way to combine strings with variables (like in the `printf()` function) and pass them as parameters to `SDL_Reimu_CheckError()`, so 2 lines will have to do for now. Tragic, I know.

---
# Building
### Windows
(Coming soon)
### MacOS
(Coming soon)
### Linux
(Coming soon)
