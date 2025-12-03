#pragma once

// ==============================
// Core Engine
// ==============================
#include "RealEngine/Core/Application.h"
#include "RealEngine/Core/Assert.h"
#include "RealEngine/Core/Core.h"
#include "RealEngine/Core/Input.h"
#include "RealEngine/Core/KeyCodes.h"
#include "RealEngine/Core/Logger.h"
#include "RealEngine/Core/MouseCodes.h"
#include "RealEngine/Core/Profiler.h"
#include "RealEngine/Core/Dialogs.h"

// ==============================
// Events
// ==============================
#include "RealEngine/Events/Event.h"
#include "RealEngine/Events/KeyEvents.h"
#include "RealEngine/Events/MouseEvents.h"
#include "RealEngine/Events/WindowEvents.h"
#include "RealEngine/Events/ProjectEvents.h"

// ==============================
// Asset
// ==============================
#include "RealEngine/Asset/Asset.h"

// ==============================
// Rendering
// ==============================
#include "RealEngine/Render/RenderCommands.h"

// ==============================
// Utilities
// ==============================
#include "RealEngine/Utils/FileHelper.h"

// ==============================
// Formatters
// ==============================
#include "RealEngine/Formatter/GLMFormatter.h"
#include "RealEngine/Formatter/RealEngineFormatter.h"
#include "RealEngine/Formatter/STDFormatter.h"
#include "RealEngine/Formatter/YAMLFormatter.h"

// ==============================
// Types
// ==============================
#include "RealEngine/Types/HashMap.h"

// ==============================
// External Graphics Libraries
// ==============================
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// ==============================
// Standard Library
// ==============================
#include <algorithm>
#include <array>
#include <chrono>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <optional>
#include <random>
#include <sstream>
#include <string>
#include <thread>
#include <utility>
#include <vector>
