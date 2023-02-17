#pragma once

#include <cstdint>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <map>

#include "../ImGuiExternal/Directories/ImGui/imgui.h"
#include "../ImGuiExternal/Directories/ImGui/imgui_impl_dx9.h"
#include "../ImGuiExternal/Directories/ImGui/imgui_internal.h"
#include "../ImGuiExternal/Directories/ImGui/imgui_impl_win32.h"

namespace customgui {
    bool tab ( const char* label, bool selected );
}