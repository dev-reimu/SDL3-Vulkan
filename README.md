A simple SDL3 program that ties in with the Vulkan rendering API.

The SDL3 side is written using their "main callbacks" system, giving the operating system more control over when the program updates.
For example, it plays nicer with Wayland.
