# ZZX Engine

An Interactive application with real-time 3D graphics

## Engine Architecture

- Build configuration: premake

- External libraries:
    - glad: OpenGL Functions Loader
    - glfw: OpenGL Context
    - glm: Math
    - imgui: GUI 
    - spdlog: Logging
    - stb: Texture Loading
    - yaml: scene serialization

## Game Engine (Data Transformation Machine) Structure

`Editor` and `Sandbox` are client applications. 

`ZZX` is the core engine.

Workflow

1.	Initialize logging functionality
    - Create client and core engine logger and declare log macros

2.	Create the application
    - Initialize `Application`
        - Create `LayerStack`
        - Create `IWindow` and sets its event callback
        - Initialize `Renderer`
        - Create `ImguiLayer`
    - 
3.	Run the application
4.	Shutdown the application



INSERT inheritance pics

- Entry point: `EntryPoint.h`
    - contains `main()` that initializes `Log`, creates, runs, and shutdowns the `Application` if necessary. 

- `Application` layer: 
    - contains `IWindow`, `LayerStack`, `ImguiLayer`

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


- Precompiled header `zzxpch.h` is used to reduce compilation time.
    - Files that are not frequently modified (such as STL) are included. 
    - Precompiled headers may reduce readability by hiding dependencies. Thus, only some selected headers are included.

## Credits

Inspired by Hazel Engine

## TODOs

- LJ spdlog class