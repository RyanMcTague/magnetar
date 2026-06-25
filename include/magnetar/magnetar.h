#pragma once

#include "magnetar/assets/asset.h"
#include "magnetar/assets/asset_manager.h"

#include "magnetar/containers/tree.h"

#include "magnetar/core/base.h"
#include "magnetar/core/application.h"
#include "magnetar/core/time.h"
#include "magnetar/core/uuid.h"
#include "magnetar/core/window.h"
#include "magnetar/core/game_layer.h"

#include "magnetar/events/event_callback.h"
#include "magnetar/events/event_handle.h"
#include "magnetar/events/event_system.h"

#include "magnetar/filesystem/file_system.h"
#include "magnetar/filesystem/memory_file_system.h"
#include "magnetar/filesystem/native_file_system.h"

#include "magnetar/input/enums.h"
#include "magnetar/input/input_action.h"
#include "magnetar/input/input_code.h"
#include "magnetar/input/input_device.h"
#include "magnetar/input/input_system.h"
#include "magnetar/input/keyboard_device.h"
#include "magnetar/input/mapped_input_code.h"
#include "magnetar/input/mouse_device.h"

#include "magnetar/math/rect.h"

#include "magnetar/renderer/enums.h"
#include "magnetar/renderer/buffer_mask.h"
#include "magnetar/renderer/graphics_device.h"
#include "magnetar/renderer/renderer.h"
#include "magnetar/renderer/buffer_layout.h"
#include "magnetar/renderer/index_buffer.h"
#include "magnetar/renderer/material.h"
#include "magnetar/renderer/mesh.h"
#include "magnetar/renderer/font.h"
#include "magnetar/renderer/camera.h"
#include "magnetar/renderer/render_command.h"
#include "magnetar/renderer/shader_library.h"
#include "magnetar/renderer/vertex_array.h"
#include "magnetar/renderer/shader.h"
#include "magnetar/renderer/texture.h"
#include "magnetar/renderer/vertex_buffer.h"

#include "magnetar/scene/components.h"
#include "magnetar/scene/scene.h"
#include "magnetar/scene/entity.h"

#include "magnetar/scripting/enums.h"
#include "magnetar/scripting/script_class.h"
#include "magnetar/scripting/script_engine.h"
#include "magnetar/scripting/script_instance.h"
#include "magnetar/scripting/script_runtime.h"

#include "magnetar/utils/string_utils.h"
#include "magnetar/utils/enum_utils.h"
#include "magnetar/utils/image_utils.h"