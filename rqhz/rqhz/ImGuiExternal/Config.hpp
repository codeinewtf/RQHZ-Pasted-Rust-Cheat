#pragma once

#include "Archivex.hpp"

#include <iostream>
#include <windows.h>
#include <thread>
#include <random>
#include <d3d9.h>
#include <dinput.h>
#include <Mmsystem.h>
#include <mciapi.h>
#include <Mmsystem.h>
#include <TlHelp32.h>
#include <mciapi.h>
#include <strsafe.h> 
#include <Uxtheme.h>
#include <windows.h>
#include <string>
#include <stdio.h>
#include <array>
#include <Psapi.h>
#include <dwmapi.h>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <ctime>
#include <time.h>
#include <cctype>
#include <iomanip>
#include <sstream>
#include <string>
#include <regex>
#include <ProcessSnapshot.h>
#include <filesystem>
#include <ShlObj_core.h>
#include <Windows.h>
#include <iostream>
#include <tlhelp32.h>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <string>
#include <tchar.h>
#include <string.h>
#include <urlmon.h>
#include <Windows.h>
#include <Mmsystem.h>
#include <Windows.h>
#include <mmstream.h>
#include <fstream>
#include <iostream>
#include <tlhelp32.h>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <string>
#include <tchar.h>
#include <string.h>
#include <urlmon.h>
#include <Windows.h>
#include <Mmsystem.h>
#include <Windows.h>
#include <mmstream.h>
#include <fstream>
#include <wingdi.h>
#include <sapi.h>

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "magnification.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "ntdll.lib")
#pragma comment(lib,"urlmon.lib")

#include "../ImGuiExternal/Directories/ImGui/imgui.h"
#include "../ImGuiExternal/Directories/ImGui/imgui_impl_dx9.h"
#include "../ImGuiExternal/Directories/ImGui/imgui_internal.h"
#include "../ImGuiExternal/Directories/ImGui/imgui_impl_win32.h"

class c_config
{
private:
	std::filesystem::path path;
	std::vector<std::string> configs;

public:
	void run( );
	void run2( );
	void load( size_t id );
	void save( size_t id ) const;
	void add( std::string name );
	void remove( size_t id );
	void rename( size_t item, std::string new_name );
	void reset( );

	constexpr auto &get_configs( ) {
		return configs;
	};
	constexpr auto &get_path( ) {
		return path;
	};

	struct
	{
		//ImGui Menu Stuff
		ImVec2 WindowPos;
		float WindowX, WindowY;
		ImVec2 SubWindowPos;
		ImFont *espfont{ nullptr };
		ImFont *iconfont{ nullptr };
		ImFont *gilroy_big{ nullptr };
		ImFont *gilroy_mini{ nullptr };
		ImFont *gilroy_medium{ nullptr };
		//Settings
		int width = GetSystemMetrics( SM_CXSCREEN );
		int height = GetSystemMetrics( SM_CYSCREEN );
		int currentColumn{ 1 };
		bool showing{ false };
		int hsbind{ VK_INSERT };
		//esp
		bool esp{ false };
		bool name{ false };
		bool boxesp{ false };
		bool health{ false };
		bool weapon{ false };
		bool fillrect{ false };
		bool distance{ false };
		bool snaplines{ false };
		bool prefabesp{ false };
		bool ores{ false };
		bool loots{ false };
		bool traps{ false };
		bool collectables{ false };
		int playerdistance{ 100 };
		int prefabdistance{ 100 };
		//aim
		bool aimbot{ false };
		bool silentaim{ false };
		float aimfov{ 100.f };

		//Main
		float m_reload_time{ 0.f };
		float m_reload_duration{ 0.f };
		float fly_height{ 0.f };
		float fly_direction{ 0.f };
		float m_height{ 0.f };
		float m_direction{ 0.f };
		float bulletsize{ 0.5f };
		float RecoilYaw{ 0.5f };
		float RecoilPitch{ 0.5f };
		float repeatdelay{ 0.06f };
		bool timechanger{ false };
		bool fakeadmin{ false };
		bool noanimation{ false };
		bool noflashbang{ false };
		bool noviewdamage{ false };
		bool cullingesp{ false };
		bool nosway{ false };
		bool thickbullet{ false };
		bool flyhackbar{ false };
		bool flyhack{ false };
		bool airjump{ false }; 
		bool chams{ false };
		bool infinitejump{ false };
		bool spiderman{ false };
		bool norecoil{ false };
		bool fastshoot{ false };
		float slowbullet{ 1.2f };
		bool nospread{ false };
		bool reloadindicator{ false };
		bool omnisprint{ false };
		bool antiflyhackkick{ false };
		bool beautifulnight{ false };
		bool instantbow{ false };
		bool instantcompound{ false };
		bool instanteoka{ false };
		bool automatic{ false };
		bool shootincopter{ false };
		float clienttime{ 12.f };
		float playerfov{ 90.f };
	} Includes;
}; inline auto config = c_config( );