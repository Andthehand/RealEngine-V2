#pragma once

#define GLM_ENABLE_EXPERIMENTAL

// ==============================
// Core Engine
// ==============================
#include "RealEngine/Core/Application.h"
#include "RealEngine/Core/Assert.h"
#include "RealEngine/Core/Core.h"
#include "RealEngine/Core/FileDialogs.h"
#include "RealEngine/Core/Input.h"
#include "RealEngine/Core/KeyCodes.h"
#include "RealEngine/Core/Logger.h"
#include "RealEngine/Core/MouseCodes.h"
#include "RealEngine/Core/Project.h"
#include "RealEngine/Core/ImGuiLogSink.h"

// ==============================
// Events
// ==============================
#include "RealEngine/Events/Event.h"
#include "RealEngine/Events/KeyEvents.h"
#include "RealEngine/Events/MouseEvents.h"
#include "RealEngine/Events/WindowEvents.h"
#include "RealEngine/Events/ProjectEvents.h"

// ==============================
// Rendering
// ==============================
#include "RealEngine/Render/Buffer.h"
#include "RealEngine/Render/EditorCamera.h"
#include "RealEngine/Render/Framebuffer.h"
#include "RealEngine/Render/RenderCommands.h"
#include "RealEngine/Render/Shader.h"
#include "RealEngine/Render/Texture.h"
#include "RealEngine/Render/VertexArray.h"

// ==============================
// Scene
// ==============================
#include "RealEngine/Scene/Components.h"
#include "RealEngine/Scene/ComponentSerializer.h"
#include "RealEngine/Scene/Entity.h"
#include "RealEngine/Scene/Scene.h"

// ==============================
// Asset
// ==============================
#include "RealEngine/Asset/Asset.h"
#include "RealEngine/Asset/AssetManager.h"

// ==============================
// Scripting
// ==============================
#include "RealEngine/Scripting/ScriptEngine.h"

// ==============================
// Types
// ==============================
#include "RealEngine/Types/Layer.h"
#include "RealEngine/Types/RingBuffer.h"
#include "RealEngine/Types/StringHash.h"
#include "RealEngine/Types/UUID.h"
#include "RealEngine/Types/HashMap.h"

// ==============================
// Formatters
// ==============================
#include "RealEngine/Formatter/GLMFormatter.h"
#include "RealEngine/Formatter/RealEngineFormatter.h"
#include "RealEngine/Formatter/STDFormatter.h"
#include "RealEngine/Formatter/YAMLFormatter.h"