# Magnetar

A C++ game engine framework with C# scripting, OpenGL rendering, and an Entity-Component-System architecture.

---

## Overview

Magnetar is a 2D game engine. It provides a complete game development foundation including a rendering pipeline, scene management, an asset system, input handling, and a C# scripting runtime backed by Mono.

---

## Features

- **Rendering** — OpenGL-based renderer with support for 2D sprites, 3D meshes, shaders, materials, and cameras (orthographic and perspective)
- **Entity-Component System** — Data-oriented entity management powered by [EnTT](https://github.com/skypjack/entt)
- **C# Scripting** — Game logic written in C# via an embedded Mono runtime; scripts access engine APIs through an `InternalCalls` P/Invoke bridge
- **Asset System** — YAML-based asset registry with loaders for textures (stb_image), shaders, materials, and 3D models (Assimp)
- **Input System** — Named action mappings over keyboard and mouse via GLFW
- **Event System** — Type-safe publish/subscribe event bus
- **Layer Stack** — Middleware-style layer composition for the game loop
- **File System** — Abstracted file system with native and in-memory implementations

---

## Architecture

```
Application
└── LayerStack
    └── GameLayer
        ├── Scene  (EnTT registry)
        │   └── Entity / Components
        ├── Renderer
        │   ├── GraphicsDevice  (OpenGL backend)
        │   ├── Shader / Material / Texture
        │   └── Renderer2D
        ├── ScriptEngine
        │   ├── MonoRuntime  (Mono JIT)
        │   └── ScriptInstance  (OnStart / OnUpdate)
        ├── AssetManager
        │   └── Loaders: Texture, Shader, Material, Mesh
        ├── InputSystem
        │   └── Devices: Keyboard, Mouse (GLFW)
        └── EventSystem
```

### Scripting

Scripts inherit from the managed `Entity` class and override lifecycle methods:

```csharp
using Magnetar.Core;

class Player : Entity
{
    void OnStart()  { /* called once */ }
    void OnUpdate(float dt) { /* called every frame */ }
}
```

Components are accessed through a generic API:

```csharp
var rb = GetComponent<RigidBody2DComponent>();
rb.Velocity = new Vector2(100f, 0f);
```

The `ScriptComponent` in C++ links an entity to its managed class by name. The engine loads the compiled C# assembly at startup and creates instances per entity as the scene runs.

---

## Building

### Prerequisites

- CMake 3.28+
- Conan 2.x
- A C++20-capable compiler (tested on macOS/clang)
- .NET 8 SDK (to recompile C# scripting library)
- Mono (bundled under `vendor/mono/`)

### Steps

```bash
# Install dependencies
conan install . --output-folder=.conan --build=missing -s build_type=Release

# Configure
cmake --preset=default

# Build
cmake --build --preset=default
```

Build options (pass with `-D` to cmake):

| Option | Default | Description |
|---|---|---|
| `MAGNETAR_BUILD_SHARED` | OFF | Build as a shared library instead of static |
| `MAGNETAR_BUILD_SANDBOX` | ON | Build the sample application |

### Output

- `libmagnetar.a` — engine static library
- `sample` — sandbox executable

---

## Sample Application

`sample/main.cpp` demonstrates the engine with a 2D scene:

- WASD + Space + ESC input action bindings
- Entities with sprites, rigidbodies, and script components
- `Player` and `Enemy` C# scripts driving entity behavior
- Asset loading from a YAML manifest

Run the sample after building:

```bash
./build/sample
```

---

## Dependencies

| Library | Version | Purpose |
|---|---|---|
| [EnTT](https://github.com/skypjack/entt) | 3.16.0 | Entity-Component-System |
| [GLFW](https://www.glfw.org) | 3.4 | Window and input |
| [GLM](https://github.com/g-truc/glm) | 1.0.1 | Math (vectors, matrices) |
| [spdlog](https://github.com/gabime/spdlog) | 1.17.0 | Logging |
| [fmt](https://github.com/fmtlib/fmt) | 12.1.0 | String formatting |
| [yaml-cpp](https://github.com/jbeder/yaml-cpp) | 0.9.0 | Asset manifest parsing |
| [Assimp](https://github.com/assimp/assimp) | 6.0.2 | 3D model loading |
| [magic_enum](https://github.com/Neargye/magic_enum) | 0.9.7 | Compile-time enum reflection |
| [stb_image](https://github.com/nothings/stb) | — | Texture loading (bundled) |
| [Mono](https://www.mono-project.com) | 2.0 | C# scripting runtime (bundled) |

Dependencies are managed via Conan; Mono and stb_image are vendored directly.

---

## Platform

Currently macOS only. GLFW and Mono are cross-platform, but the Mono library is only bundled for macOS. Windows/Linux support would require supplying the appropriate Mono binaries and adjusting the CMake platform guard.

