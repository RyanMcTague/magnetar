target_sources(magnetar
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS include
        FILES
            include/magnetar/assets/asset.h
            include/magnetar/assets/asset_manager.h
            include/magnetar/assets/resouce_loader.h
            include/magnetar/assets/asset_handle.h
            include/magnetar/assets/loaders/texture_loader.h
            include/magnetar/assets/loaders/shader_loader.h
            include/magnetar/assets/loaders/font_loader.h

            include/magnetar/containers/tree.h

            include/magnetar/core/time.h
            include/magnetar/core/application.h
            include/magnetar/core/window.h
            include/magnetar/core/logger.h
            include/magnetar/core/base.h
            include/magnetar/core/uuid.h
            include/magnetar/core/layer.h
            include/magnetar/core/layer_stack.h
            include/magnetar/core/game_layer.h

            include/magnetar/events/event_handle.h
            include/magnetar/events/event_system.h
            include/magnetar/events/event_callback.h

            include/magnetar/filesystem/memory_file_system.h
            include/magnetar/filesystem/native_file_system.h
            include/magnetar/filesystem/file_system.h

            include/magnetar/input/input_device.h
            include/magnetar/input/input_action.h
            include/magnetar/input/input_code.h
            include/magnetar/input/enums.h
            include/magnetar/input/mouse_device.h
            include/magnetar/input/mapped_input_code.h
            include/magnetar/input/keyboard_device.h
            include/magnetar/input/input_system.h

            include/magnetar/math/rect.h

            include/magnetar/platforms/glfw/glfw_keyboard_device.h
            include/magnetar/platforms/glfw/glfw_mouse_device.h
            include/magnetar/platforms/glfw/glfw_window.h

            include/magnetar/renderer/buffer_layout.h
            include/magnetar/renderer/enums.h
            include/magnetar/renderer/graphics_device.h
            include/magnetar/renderer/index_buffer.h
            include/magnetar/renderer/shader_library.h
            include/magnetar/renderer/shader.h
            include/magnetar/renderer/texture.h
            include/magnetar/renderer/font.h
            include/magnetar/renderer/buffer_mask.h
            include/magnetar/renderer/renderer.h
            include/magnetar/renderer/camera.h
            include/magnetar/renderer/vertex_array.h
            include/magnetar/renderer/vertex_buffer.h
            include/magnetar/renderer/renderer2d.h

            include/magnetar/renderer/backend/opengl/glad.h
            include/magnetar/renderer/backend/opengl/helpers.h
            include/magnetar/renderer/backend/opengl/texture.h
            include/magnetar/renderer/backend/opengl/index_buffer.h
            include/magnetar/renderer/backend/opengl/khrplatform.h
            include/magnetar/renderer/backend/opengl/shader_compiler.h
            include/magnetar/renderer/backend/opengl/shader.h
            include/magnetar/renderer/backend/opengl/vertex_buffer.h
            include/magnetar/renderer/backend/opengl/vertex_array.h
            include/magnetar/renderer/backend/opengl/graphics_device.h

            include/magnetar/scene/scene.h
            include/magnetar/scene/components.h
            include/magnetar/scene/entity_handle.h
            include/magnetar/scene/entity.h

            include/magnetar/scripting/script_class.h
            include/magnetar/scripting/script_instance.h
            include/magnetar/scripting/script_runtime.h

            include/magnetar/scripting/enums.h
            include/magnetar/scripting/script_engine.h
            include/magnetar/scripting/script_registry.h
            include/magnetar/scripting/script_field.h

            include/magnetar/scripting/mono/mono_runtime.h
            include/magnetar/scripting/mono/mono_script_class.h
            include/magnetar/scripting/mono/mono_script_instance.h

            include/magnetar/utils/enum_utils.h
            include/magnetar/utils/string_utils.h
            include/magnetar/utils/image_utils.h

            include/magnetar/vendor/stb_image.h

            include/magnetar/magnetar.h

    PRIVATE
        src/assets/asset_manager.cpp
        src/assets/loaders/texture_loader.cpp
        src/assets/loaders/shader_loader.cpp
        src/assets/loaders/font_loader.cpp

        src/core/application.cpp
        src/core/logger.cpp
        src/core/window.cpp
        src/core/time.cpp
        src/core/layer_stack.cpp
        src/core/uuid.cpp
        src/core/game_layer.cpp

        src/events/event_system.cpp

        src/filesystems/file_system.cpp
        src/filesystems/native_file_system.cpp
        src/filesystems/memory_file_system.cpp

        src/input/input_system.cpp
        src/input/keyboard_device.cpp
        src/input/mouse_device.cpp
        src/input/input_action.cpp

        src/platforms/glfw/glfw_window.cpp
        src/platforms/glfw/glfw_keyboard_device.cpp
        src/platforms/glfw/glfw_mouse_device.cpp

        src/renderer/shader.cpp
        src/renderer/shader_library.cpp
        src/renderer/buffer_layout.cpp
        src/renderer/renderer.cpp
        src/renderer/camera.cpp
        src/renderer/font.cpp
        src/renderer/renderer2d.cpp

        src/renderer/backend/opengl/glad.cpp
        src/renderer/backend/opengl/helpers.cpp
        src/renderer/backend/opengl/shader_compiler.cpp
        src/renderer/backend/opengl/shader.cpp
        src/renderer/backend/opengl/index_buffer.cpp
        src/renderer/backend/opengl/vertex_buffer.cpp
        src/renderer/backend/opengl/vertex_array.cpp
        src/renderer/backend/opengl/texture.cpp
        src/renderer/backend/opengl/graphics_device.cpp

        src/scene/scene.cpp
        src/scene/entity.cpp

        src/scripting/script_engine.cpp
        src/scripting/script_registry.cpp

        src/scripting/mono/mono_runtime.cpp
        src/scripting/mono/mono_script_class.cpp
        src/scripting/mono/mono_script_instance.cpp

        src/utils/string_utils.cpp
        src/utils/image_utils.cpp
)
