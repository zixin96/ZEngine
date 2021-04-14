# ZZX Engine

## Engine Architecture

- Build configuration: premake

- External libraries:
    - glad: OpenGL Functions Loader
    - glfw: OpenGL Context
    - glm: Math
    - imgui: GUI 
    - spdlog: Logging
    - stb: Texture Loading

## Game Engine Structure

- Entry point

The solution contains two main projects: an engine project (called "ZZX") and an application project (called "Sandbox"). External dependencies are listed. Sandbox is the default startup project. Since ZZX controls the main function, `main()` resides in ZZX's `EntryPoint.h`. Sandbox's `Game.cpp` will include this file so that the main() will be called when running the application. 

- Application layer
- Window layer
	- Input
	- Events
- Renderer
- Render API abstraction (OpenGL)
- Debugging support
    - 'Log' class is a wrapper around `spdlog` that outputs log messages to console and `ZZX.log`.
    - Profiling uses `<chrono>` and supports chrome tracing.
- Scripting language
- Memory system
- Entity-component system (ECS)
- Physics
- File I/O, Virtual File System (VFS)
- Build system


## Credits

Inspired by Hazel Engine