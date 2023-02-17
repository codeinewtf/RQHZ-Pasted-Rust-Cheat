#include "Imports.hpp"
#include "Gui.hpp"
#define LOADER_BRAND "rust cheat"
#define WINDOW_WIDTH  475
#define WINDOW_HEIGHT 300
bool loader_active = true;

LPCSTR TargetProcess = "RustClient.exe";
bool ShowMenu = true;
bool CreateConsole = true;

IDirect3DTexture9 *byteImage = nullptr;

struct CurrentProcess {
	DWORD ID;
	HANDLE Handle;
	HWND Hwnd;
	WNDPROC WndProc;
	int WindowWidth;
	int WindowHeight;
	int WindowLeft;
	int WindowRight;
	int WindowTop;
	int WindowBottom;
	LPCSTR Title;
	LPCSTR ClassName;
	LPCSTR Path;
}Process;

struct OverlayWindow {
	WNDCLASSEX WindowClass;
	HWND Hwnd;
	LPCSTR Name;
}Overlay;

struct DirectX9Interface {
	IDirect3D9Ex *IDirect3D9 = NULL;
	IDirect3DDevice9Ex *pDevice = NULL;
	D3DPRESENT_PARAMETERS pParameters = { NULL };
	MARGINS Margin = { -1 };
	MSG Message = { NULL };
}DirectX9;

std::string GetFormattedTime( ) {
	time_t rawtime;
	tm timeinfo = {};
	char buffer[80];
	time( &rawtime );
	localtime_s( &timeinfo, &rawtime );
	auto suffix = timeinfo.tm_hour >= 12 ? ( " pm" ) : ( " am" );
	if ( timeinfo.tm_hour > 12 )
		timeinfo.tm_hour -= 12;
	strftime( buffer, sizeof( buffer ), ( "%H:%M" ), &timeinfo );
	return std::string( buffer ) + suffix;
}

std::string ReadFiles( std::string file )
{
	std::string line;
	std::ifstream myfile( file );
	if ( myfile.is_open( ) )
	{
		while ( getline( myfile, line ) )
		{
			return line;
		}
		myfile.close( );
	}
}

std::string removeSpaces( std::string str )
{
	str.erase( remove( str.begin( ), str.end( ), ' ' ), str.end( ) );
	return str;
}

std::string file_pass = ReadFiles( "C:\\rainycheats\\login.json" );
std::string fileusername = removeSpaces( file_pass.substr( file_pass.find( ">" ) + 1 ) );

void Crosshair( ) {
	float midX = GetSystemMetrics( SM_CXSCREEN ) / 2;
	float midY = GetSystemMetrics( SM_CYSCREEN ) / 2;

	visuals::Line( { midX, ( midY - 8 ) }, { midX, ( midY - 4 ) }, ImColor( 255, 255, 255 ), 1.f );
	visuals::Line( { ( midX - 8 ), midY }, { ( midX - 4 ), midY }, ImColor( 255, 255, 255 ), 1.f );

	visuals::Line( { midX, ( midY + 8 ) }, { midX, ( midY + 4 ) }, ImColor( 255, 255, 255 ), 1.f );
	visuals::Line( { ( midX + 8 ), midY }, { ( midX + 4 ), midY }, ImColor( 255, 255, 255 ), 1.f );
}

void Watermark( )
{
	auto s = ImVec2( ImGui::GetWindowSize( ).x - ImGui::GetStyle( ).WindowPadding.x * 2, ImGui::GetWindowSize( ).y - ImGui::GetStyle( ).WindowPadding.y * 2 );
	auto p = ImVec2( ImGui::GetWindowPos( ).x + ImGui::GetStyle( ).WindowPadding.x, ImGui::GetWindowPos( ).y + ImGui::GetStyle( ).WindowPadding.y );

	std::string name_software = "NiggaHack.xyz |";
	std::string stats = " | " + GetFormattedTime( );

	//1 bg
	ImGui::GetForegroundDrawList( )->AddRectFilledMultiColor( ImVec2( p.x + 10, p.y + 10 ), ImVec2( p.x + 267, p.y + 37 ), ImColor( 14, 14, 14, 110 ), ImColor( 10, 10, 10 ), ImColor( 14, 14, 14, 110 ), ImColor( 10, 10, 10 ) );
	//2 bg
	ImGui::GetForegroundDrawList( )->AddRectFilled( ImVec2( p.x + 14, p.y + 14 ), ImVec2( p.x + 263, p.y + 33 ), ImColor( 10, 10, 10 ), 1 );
	// text
	ImGui::GetForegroundDrawList( )->AddText( ImVec2( p.x + 20, p.y + 18 ), ImColor( 87, 88, 88 ), name_software.c_str( ) );
	ImGui::GetForegroundDrawList( )->AddText( ImVec2( p.x + ImGui::CalcTextSize( name_software.c_str( ) ).x + 25, p.y + 18 ), ImColor( 189, 191, 209 ), fileusername.c_str( ) );
	ImGui::GetForegroundDrawList( )->AddText( ImVec2( p.x + ImGui::CalcTextSize( fileusername.c_str( ) ).x + ImGui::CalcTextSize( stats.c_str( ) ).x * 1.8, p.y + 18 ), ImColor( 87, 88, 88 ), stats.c_str( ) );
}

void aimmark( )
{
	Vector2 aimpos;
	if ( !loops::aimbone.is_empty( ) )
	{
		if ( entityloop::camera->WorldToScreen( &entityloop::projection_matrix, loops::aimbone, &aimpos ) )
			visuals::StrokeText( aimpos.x - 3.25f, aimpos.y - 9.25f, ImColor( 255, 0, 0 ), "+" );
	}
}

void Render( ) {
	ImGui_ImplDX9_NewFrame( );
	ImGui_ImplWin32_NewFrame( );
	ImGui::NewFrame( );
	{
		RECT screen_rect;
		GetWindowRect( GetDesktopWindow( ), &screen_rect );
		auto x = float( screen_rect.right - WINDOW_WIDTH ) / 2.f;
		auto y = float( screen_rect.bottom - WINDOW_HEIGHT ) / 2.f;

		LPCTSTR pszPic = "C:\\rainycheats\\avatar.jpg";
		if ( !byteImage )
			D3DXCreateTextureFromFileA( DirectX9.pDevice, pszPic, &byteImage );

		if ( GetAsyncKeyState( config.Includes.hsbind ) & 1 )
			config.Includes.showing = !config.Includes.showing;
		if ( config.Includes.showing ) {
			ImGui::SetNextWindowSize( ImVec2( 550, 440 ) );
			ImGui::Begin( "rainy", nullptr, ImGuiWindowFlags_NoDecoration );
			{
				auto draw = ImGui::GetWindowDrawList( );
				ImVec2 pos = ImGui::GetWindowPos( );
				ImVec2 size = ImGui::GetWindowSize( );

				/*header decorations*/
				draw->AddRectFilled( pos, ImVec2( pos.x + size.x, pos.y + 45 ), ImColor( 18, 16, 40 ), 2.0f, ImDrawFlags_RoundCornersTop );
				draw->AddRectFilled( ImVec2( pos.x, pos.y + 45 ), ImVec2( pos.x + size.x, pos.y + 47 ), ImColor( 60, 57, 101, 180 ) );

				//draw->AddImage(cheat_logo, ImVec2(pos.x + 50, pos.y + 50), ImVec2(pos.x + 50, pos.y + 50), ImVec2(0, 0), ImVec2(1, 1), ImColor(1.0f, 1.0f, 1.0f, 0.6f));
				draw->AddText( ImVec2( pos.x + 10, pos.y + 16 ), ImColor( 1.0f, 1.0f, 1.0f ), "hooK.xyz" );

				draw->AddImageRounded( byteImage, ImVec2( pos.x + size.x - 30, pos.y + 13 ), ImVec2( pos.x + size.x - 10, pos.y + 33 ), ImVec2( 0, 0 ), ImVec2( 1, 1 ), ImColor( 1.0f, 1.0f, 1.0f ), 20.0f );
				draw->AddText( ImVec2( pos.x + size.x - 32 - ImGui::CalcTextSize( fileusername.c_str( ) ).x, pos.y + 16 ), ImColor( 1.0f, 1.0f, 1.0f ), fileusername.c_str( ) );

				ImGui::SetCursorPos( ImVec2( 190, 11 ) );
				ImGui::BeginGroup( );
				if ( customgui::tab( "aim", 0 == config.Includes.currentColumn ) ) config.Includes.currentColumn = 0;
				ImGui::SameLine( );
				if ( customgui::tab( "visuals", 1 == config.Includes.currentColumn ) ) config.Includes.currentColumn = 1;
				ImGui::SameLine( );
				if ( customgui::tab( "misc", 2 == config.Includes.currentColumn ) ) config.Includes.currentColumn = 2;
				ImGui::SameLine( );
				if ( customgui::tab( "config", 3 == config.Includes.currentColumn ) ) config.Includes.currentColumn = 3;
				ImGui::EndGroup( );

				ImGui::SetCursorPos( ImVec2( 100, 11 ) );
				if ( customgui::tab( "exit", 0 ) )
				{
					config.Includes.fastshoot = false;
					config.Includes.playerfov = 90.f;
					config.Includes.RecoilPitch = 1;
					config.Includes.RecoilYaw = 1;
					Sleep( 150 );
					exit( 0 );
				}

				switch ( config.Includes.currentColumn ) {
				case 0:
					ImGui::SetCursorPos( ImVec2( 20, 65 ) );
					ImGui::BeginChild( "Aimbot", ImVec2( 250, 355 ) );
					{
						ImGui::Checkbox( "Aimbot", &config.Includes.aimbot );
						ImGui::Checkbox( "SilentAim", &config.Includes.silentaim );
						if ( config.Includes.aimbot )
							config.Includes.silentaim = false;
						if ( config.Includes.silentaim )
							config.Includes.aimbot = false;
						if ( config.Includes.aimbot || config.Includes.silentaim )
						{
							ImGui::SliderFloat( "Aim FOV", &config.Includes.aimfov, 5.f, 360.f, "%.2f" );
							ImGui::Combo( "Aim Bone", &aimBone, aimBoneStr, 5 );
							//ImGui::Combo ( "Aim Bone", &config.Includes.aimBone, config.Includes.Aimboneitems, sizeof ( config.Includes.aimBone ) );
						}
					}
					ImGui::EndChild( );

					ImGui::SetCursorPos( ImVec2( 280, 65 ) );
					ImGui::BeginChild( "Weapon", ImVec2( 250, 167 ) );
					{
						ImGui::Checkbox( "No Sway", &config.Includes.nosway );
						ImGui::Checkbox( "Fast Bow", &config.Includes.instantbow );
						ImGui::Checkbox( "No Recoil", &config.Includes.norecoil );
						ImGui::Checkbox( "Automatic", &config.Includes.automatic );
						ImGui::Checkbox( "Thickbullet", &config.Includes.thickbullet );
						ImGui::Checkbox( "Instant Eoka", &config.Includes.instanteoka );
						ImGui::Checkbox( "Instant Compound", &config.Includes.instantcompound );
					}
					ImGui::EndChild( );

					ImGui::SetCursorPos( ImVec2( 280, 242 ) );
					ImGui::BeginChild( "Settings", ImVec2( 250, 177 ) );
					{
						if ( config.Includes.norecoil )
						{
							ImGui::SliderFloat( "Control X", &config.Includes.RecoilYaw, 0.f, 1.f, "%.2f" );
							ImGui::SliderFloat( "Control Y", &config.Includes.RecoilPitch, 0.f, 1.f, "%.2f" );
						}

						if ( config.Includes.thickbullet )
						{
							ImGui::SliderFloat( "Bullet Size", &config.Includes.bulletsize, 0.f, 1.5f, "%.1f" );
						}
					}
					ImGui::EndChild( );
					break;
				case 1:
					ImGui::SetCursorPos( ImVec2( 20, 65 ) );
					ImGui::BeginChild( "Visuals", ImVec2( 250, 355 ) );
					{
						//ImGui::Checkbox ( "Culling Esp", &config.Includes.cullingesp );
						//ImGui::SameLine ( );
						//ImGui::Text ( "More UD But Weird" );
						ImGui::Checkbox( "Esp", &config.Includes.esp );
						if ( config.Includes.esp )
						{
							ImGui::Checkbox( "Box", &config.Includes.boxesp );
							ImGui::Checkbox( "Filled Box", &config.Includes.fillrect );
							ImGui::Checkbox( "Name", &config.Includes.name );
							ImGui::Checkbox( "Chams", &config.Includes.chams );
							ImGui::Checkbox( "Health", &config.Includes.health );
							ImGui::Checkbox( "Weapon", &config.Includes.weapon );
							ImGui::Checkbox( "Distance", &config.Includes.distance );
							ImGui::Checkbox( "SnapLines", &config.Includes.snaplines );
						}
						ImGui::Separator( );
						ImGui::Checkbox( "Prefab Esp", &config.Includes.prefabesp );
						if ( config.Includes.prefabesp )
						{
							static std::string preview = "";
							if ( ImGui::BeginCombo( "##Prefab Arrays", preview.c_str( ) ) )
							{
								preview = "";
								std::vector<std::string> vec;
								for ( size_t i = 0; i < IM_ARRAYSIZE( items ); i++ )
								{
									ImGui::Selectable( items[i], &selected[i], ImGuiSelectableFlags_::ImGuiSelectableFlags_DontClosePopups );
									if ( selected[i] )
										vec.push_back( items[i] );
								}
								for ( size_t i = 0; i < vec.size( ); i++ )
								{
									if ( vec.size( ) == 1 )
										preview += vec.at( i );
									else if ( !( i == vec.size( ) - 1 ) )
										preview += vec.at( i ) + ",";
									else
										preview += vec.at( i );
								}

								ImGui::EndCombo( );
							}
							//ImGui::Checkbox ( "Ores", &config.Includes.ores );
							//ImGui::Checkbox ( "Loot", &config.Includes.loots );
							//ImGui::Checkbox ( "Traps", &config.Includes.traps );
							//ImGui::Checkbox ( "Collectables", &config.Includes.collectables );
						}
						//ImGui::Checkbox ( "Chams", &config.Includes.chams );
					}
					ImGui::EndChild( );

					ImGui::SetCursorPos( ImVec2( 280, 65 ) );
					ImGui::BeginChild( "Settings", ImVec2( 250, 167 ) );
					{
						ImGui::SetCursorPos( ImVec2( -5, 0 ) );
						ImGui::SliderInt( "Max Esp Distance", &config.Includes.playerdistance, 5, 375, "%.1f" );
						ImGui::SetCursorPos( ImVec2( -5, 35 ) );
						ImGui::SliderInt( "Max Prefab Distance", &config.Includes.prefabdistance, 5, 250, "%.1f" );
						ImGui::SetCursorPos( ImVec2( -5, 70 ) );
						ImGui::SliderFloat( "Player Fov", &config.Includes.playerfov, 90.f, 150.f, "%.2f" );
						if ( config.Includes.timechanger )
						{
							ImGui::SetCursorPos( ImVec2( -5, 135 ) );
							ImGui::SliderFloat( "Client Time", &config.Includes.clienttime, 0.f, 14.f, "%.1f" );
						}
					}
					ImGui::EndChild( );

					ImGui::SetCursorPos( ImVec2( 280, 242 ) );
					ImGui::BeginChild( "Other", ImVec2( 250, 177 ) );
					{
						ImGui::Checkbox( "Beautiful Night", &config.Includes.beautifulnight );
						ImGui::Checkbox( "Time Changer", &config.Includes.timechanger );
					}
					ImGui::EndChild( );
					break;
				case 2:
					ImGui::SetCursorPos( ImVec2( 20, 65 ) );
					ImGui::BeginChild( "Misc", ImVec2( 250, 355 ) );
					{
						ImGui::Checkbox( "Spiderman", &config.Includes.spiderman );
						ImGui::Checkbox( "Infinite Jump", &config.Includes.infinitejump );
						ImGui::Checkbox( "Shoot In Minicopter", &config.Includes.shootincopter );
						ImGui::Checkbox( "Flyhack Reset", &config.Includes.flyhack );
						ImGui::Checkbox( "Shoot in Air", &config.Includes.airjump );
							
						ImGui::Separator( );

						ImGui::Checkbox( "Fake Admin", &config.Includes.fakeadmin );
						ImGui::Checkbox( "No Flashbang", &config.Includes.noflashbang );
					}
					ImGui::EndChild( );

					ImGui::SetCursorPos( ImVec2( 280, 65 ) );
					ImGui::BeginChild( "Rage", ImVec2( 250, 167 ) );
					{
						ImGui::Checkbox( "Nospread", &config.Includes.nospread );
						ImGui::Checkbox( "Omnisprint", &config.Includes.omnisprint );
						ImGui::Checkbox( "Instant Kill", &config.Includes.fastshoot );
					}
					ImGui::EndChild( );

					ImGui::SetCursorPos( ImVec2( 280, 242 ) );
					ImGui::BeginChild( "Exploits", ImVec2( 250, 177 ) );
					{
						ImGui::Checkbox( "Flyhack Bar", &config.Includes.flyhackbar );
						if ( config.Includes.flyhackbar )
							ImGui::Checkbox( "No Flyhack Kick", &config.Includes.antiflyhackkick );
						ImGui::Checkbox( "Reload Indicator", &config.Includes.reloadindicator );
						ImGui::Checkbox( "No Animation", &config.Includes.noanimation );
						if ( config.Includes.fastshoot )
						{
							ImGui::SetCursorPos( ImVec2( -15, 100 ) );
							ImGui::SliderFloat( "Repeat Delay(Instant Kill)", &config.Includes.repeatdelay, 0.0f, 0.15f, "%.2f" );
						}
					}
					ImGui::EndChild( );
					break;
				case 3:
					ImGui::SetCursorPos( ImVec2( 20, 65 ) );
					ImGui::BeginChild( "Config", ImVec2( 250, 470 ) );
					{
						ImGui::BeginGroup( );

						constexpr auto &config_items = config.get_configs( );
						static auto current_config = -1;

						if ( (size_t)( current_config ) >= config_items.size( ) )
							current_config = -1;

						static char buffer[32];

						ImGui::SetNextItemWidth( 134 );
						if ( ImGui::ListBox( "##Includes::config_list", &current_config, []( void *data, int idx, const char **out_text )
							{
								auto &vector = *( std::vector<std::string> * )( data );
								*out_text = vector[idx].c_str( );
								return true;
							}, &config_items, (int)( config_items.size( ) ), 5 ) && current_config != -1 ) strcpy_s( buffer, config_items[current_config].c_str( ) );

							ImGui::SetNextItemWidth( 134 );
							if ( ImGui::InputText( "##Includes::config_name", buffer, IM_ARRAYSIZE( buffer ), ImGuiInputTextFlags_EnterReturnsTrue ) )
							{
								if ( current_config != -1 )
									config.rename( current_config, buffer );
							}

							if ( ImGui::Button( "Create" ) )
								config.add( buffer );

							ImGui::SameLine( );

							if ( ImGui::Button( "Reset" ) )
								config.reset( );

							ImGui::SameLine( );

							if ( ImGui::Button( "Refresh" ) )
								config.run2( );

							if ( current_config > -1 )
							{
								if ( ImGui::Button( "Save" ) )
									config.save( current_config );

								ImGui::SameLine( );

								if ( ImGui::Button( "Load" ) )
									config.load( current_config );

								ImGui::SameLine( );

								if ( ImGui::Button( "Delete" ) )
									config.remove( current_config );
							}

							ImGui::EndGroup( );
					}
					ImGui::EndChild( );
					break;
				}
			}
			ImGui::End( );
			SetWindowLong( Overlay.Hwnd, GWL_EXSTYLE, WS_EX_TOOLWINDOW );
			UpdateWindow( Overlay.Hwnd );
			SetFocus( Overlay.Hwnd );
		}
		else {
			SetWindowLong( Overlay.Hwnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW );
			UpdateWindow( Overlay.Hwnd );
			Crosshair( );
		}
		visuals::draw_loop( );
		visuals::draw_prefab_loop( );
		aimmark( );
		if ( config.Includes.flyhackbar )
		{
			if ( config.Includes.fly_height >= 255.f ) config.Includes.fly_height = 0.f;
			if ( config.Includes.fly_height <= 0.f ) config.Includes.fly_height = 0.f;
			if ( config.Includes.fly_direction >= 255.f ) config.Includes.fly_direction = 0.f;
			if ( config.Includes.fly_direction <= 0.f ) config.Includes.fly_direction = 0.f;
			visuals::FilledRect( config.Includes.width / 2.5, config.Includes.height / 8, 250, 5, ImColor( 56, 55, 55 ) );
			visuals::FilledRect( config.Includes.width / 2.5, config.Includes.height / 8, config.Includes.fly_height, 5, ImColor( 70, 0, 222 ) );
			visuals::FilledRect( config.Includes.width / 2.5, config.Includes.height / 8.35, 250, 5, ImColor( 56, 55, 55 ) );
			visuals::FilledRect( config.Includes.width / 2.5, config.Includes.height / 8.35, config.Includes.fly_direction, 5, ImColor( 70, 0, 222 ) );
		}
		if ( config.Includes.reloadindicator && config.Includes.m_reload_duration > 0.00f && config.Includes.m_reload_time > 0.00f )
		{
			visuals::StrokeText( config.Includes.width / 1.95f, config.Includes.height / 2.05f, ImColor( 255, 255, 255 ), "Reloading: " + std::to_string( rainy.player->get_projectile( )->get_held( )->get_reload_time( ) ) );
			visuals::FilledRect( config.Includes.width / 1.95f, config.Includes.height / 2.0039f, config.Includes.m_reload_time * config.Includes.width / config.Includes.m_reload_duration / 10.f, 5, ImColor( 70, 0, 222 ) );
		}
		Watermark( );
		if ( config.Includes.aimbot || config.Includes.silentaim )
		{
			ImGui::GetBackgroundDrawList( )->AddCircle( ImVec2( config.Includes.width / 2, config.Includes.height / 2 ), config.Includes.aimfov, ImColor( 255, 255, 255 ), 0 );
		}
	}
	ImGui::EndFrame( );

	DirectX9.pDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB( 0, 0, 0, 0 ), 1.0f, 0 );
	if ( DirectX9.pDevice->BeginScene( ) >= 0 ) {
		ImGui::Render( );
		ImGui_ImplDX9_RenderDrawData( ImGui::GetDrawData( ) );
		DirectX9.pDevice->EndScene( );
	}

	HRESULT result = DirectX9.pDevice->Present( NULL, NULL, NULL, NULL );
	if ( result == D3DERR_DEVICELOST && DirectX9.pDevice->TestCooperativeLevel( ) == D3DERR_DEVICENOTRESET ) {
		ImGui_ImplDX9_InvalidateDeviceObjects( );
		DirectX9.pDevice->Reset( &DirectX9.pParameters );
		ImGui_ImplDX9_CreateDeviceObjects( );
	}
}

void MainLoop( ) {
	static RECT OldRect;
	ZeroMemory( &DirectX9.Message, sizeof( MSG ) );
	while ( DirectX9.Message.message != WM_QUIT ) {
		if ( PeekMessage( &DirectX9.Message, Overlay.Hwnd, 0, 0, PM_REMOVE ) ) {
			TranslateMessage( &DirectX9.Message );
			DispatchMessage( &DirectX9.Message );
		}
		HWND ForegroundWindow = GetForegroundWindow( );
		if ( ForegroundWindow == Process.Hwnd ) {
			HWND TempProcessHwnd = GetWindow( ForegroundWindow, GW_HWNDPREV );
			SetWindowPos( Overlay.Hwnd, TempProcessHwnd, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE );
		}

		RECT TempRect;
		POINT TempPoint;
		ZeroMemory( &TempRect, sizeof( RECT ) );
		ZeroMemory( &TempPoint, sizeof( POINT ) );

		GetClientRect( Process.Hwnd, &TempRect );
		ClientToScreen( Process.Hwnd, &TempPoint );

		TempRect.left = TempPoint.x;
		TempRect.top = TempPoint.y;
		ImGuiIO &io = ImGui::GetIO( );
		io.ImeWindowHandle = Process.Hwnd;

		if ( TempRect.left != OldRect.left || TempRect.right != OldRect.right || TempRect.top != OldRect.top || TempRect.bottom != OldRect.bottom ) {
			OldRect = TempRect;
			Process.WindowWidth = TempRect.right;
			Process.WindowHeight = TempRect.bottom;
			DirectX9.pParameters.BackBufferWidth = Process.WindowWidth;
			DirectX9.pParameters.BackBufferHeight = Process.WindowHeight;
			SetWindowPos( Overlay.Hwnd, (HWND)0, TempPoint.x, TempPoint.y, Process.WindowWidth, Process.WindowHeight, SWP_NOREDRAW );
			DirectX9.pDevice->Reset( &DirectX9.pParameters );
		}
		Render( );
	}
	ImGui_ImplDX9_Shutdown( );
	ImGui_ImplWin32_Shutdown( );
	ImGui::DestroyContext( );
	if ( DirectX9.pDevice != NULL ) {
		DirectX9.pDevice->EndScene( );
		DirectX9.pDevice->Release( );
	}
	if ( DirectX9.IDirect3D9 != NULL ) {
		DirectX9.IDirect3D9->Release( );
	}
	DestroyWindow( Overlay.Hwnd );
	UnregisterClass( Overlay.WindowClass.lpszClassName, Overlay.WindowClass.hInstance );
}

bool DirectXInit( ) {
	if ( FAILED( Direct3DCreate9Ex( D3D_SDK_VERSION, &DirectX9.IDirect3D9 ) ) ) {
		
		
		
		
		
		;
	}

	D3DPRESENT_PARAMETERS Params = { 0 };
	Params.Windowed = TRUE;
	Params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	Params.hDeviceWindow = Overlay.Hwnd;
	Params.MultiSampleQuality = D3DMULTISAMPLE_NONE;
	Params.BackBufferFormat = D3DFMT_A8R8G8B8;
	Params.BackBufferWidth = Process.WindowWidth;
	Params.BackBufferHeight = Process.WindowHeight;
	Params.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	Params.EnableAutoDepthStencil = TRUE;
	Params.AutoDepthStencilFormat = D3DFMT_D16;
	Params.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	Params.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	if ( FAILED( DirectX9.IDirect3D9->CreateDeviceEx( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, Overlay.Hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &Params, 0, &DirectX9.pDevice ) ) ) {
		DirectX9.IDirect3D9->Release( );
		return false;
	}

	IMGUI_CHECKVERSION( );
	ImGui::CreateContext( );

	ImGui_ImplWin32_Init( Overlay.Hwnd );
	ImGui_ImplDX9_Init( DirectX9.pDevice );
	ImGuiIO &io = ImGui::GetIO( ); (void)io;
	ImGuiStyle *style = &ImGui::GetStyle( );
	ImFontConfig font_config;
	io.IniFilename = nullptr;
	font_config.PixelSnapH = false;
	font_config.OversampleH = 5;
	font_config.OversampleV = 5;
	font_config.RasterizerMultiply = 1.2f;

	static const ImWchar ranges[] =
	{
		0x0020, 0x00FF, // Basic Latin + Latin Supplement
		0x0400, 0x052F, // Cyrillic + Cyrillic Supplement
		0x2DE0, 0x2DFF, // Cyrillic Extended-A
		0xA640, 0xA69F, // Cyrillic Extended-B
		0xE000, 0xE226, // icons
		0,
	};

	style->Colors[ImGuiCol_WindowBg] = ImColor( 16, 12, 29 );
	style->Colors[ImGuiCol_Button] = ImColor( 29, 31, 39 );
	style->Colors[ImGuiCol_ButtonActive] = ImColor( 48, 48, 47 );
	style->Colors[ImGuiCol_ButtonHovered] = ImColor( 38, 38, 37 );
	style->Colors[ImGuiCol_FrameBgActive] = ImColor( 80, 15, 174 );
	style->Colors[ImGuiCol_FrameBg] = ImColor( 10, 10, 10 );
	style->Colors[ImGuiCol_FrameBgHovered] = ImColor( 90, 25, 184 );

	font_config.GlyphRanges = ranges;

	io.Fonts->AddFontFromFileTTF( "C:\\Windows\\Fonts\\verdana.ttf", 13.0f, &font_config, ranges );
	DirectX9.IDirect3D9->Release( );
	return true;
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
LRESULT CALLBACK WinProc( HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam ) {
	if ( ImGui_ImplWin32_WndProcHandler( hWnd, Message, wParam, lParam ) )
		return true;

	switch ( Message ) {
	case WM_DESTROY:
		if ( DirectX9.pDevice != NULL ) {
			DirectX9.pDevice->EndScene( );
			DirectX9.pDevice->Release( );
		}
		if ( DirectX9.IDirect3D9 != NULL ) {
			DirectX9.IDirect3D9->Release( );
		}
		PostQuitMessage( 0 );
		exit( 4 );
		break;
	case WM_SIZE:
		if ( DirectX9.pDevice != NULL && wParam != SIZE_MINIMIZED ) {
			ImGui_ImplDX9_InvalidateDeviceObjects( );
			DirectX9.pParameters.BackBufferWidth = LOWORD( lParam );
			DirectX9.pParameters.BackBufferHeight = HIWORD( lParam );
			HRESULT hr = DirectX9.pDevice->Reset( &DirectX9.pParameters );
			if ( hr == D3DERR_INVALIDCALL )
				IM_ASSERT( 0 );
			ImGui_ImplDX9_CreateDeviceObjects( );
		}
		break;
	default:
		return DefWindowProc( hWnd, Message, wParam, lParam );
		break;
	}
	return 0;
}

void SetupWindow( ) {
	Overlay.WindowClass = {
		sizeof( WNDCLASSEX ), 0, WinProc, 0, 0, nullptr, LoadIcon( nullptr, IDI_APPLICATION ), LoadCursor( nullptr, IDC_ARROW ), nullptr, nullptr, Overlay.Name, LoadIcon( nullptr, IDI_APPLICATION )
	};

	RegisterClassEx( &Overlay.WindowClass );
	if ( Process.Hwnd ) {
		static RECT TempRect = { NULL };
		static POINT TempPoint;
		GetClientRect( Process.Hwnd, &TempRect );
		ClientToScreen( Process.Hwnd, &TempPoint );
		TempRect.left = TempPoint.x;
		TempRect.top = TempPoint.y;
		Process.WindowWidth = TempRect.right;
		Process.WindowHeight = TempRect.bottom;
	}

	Overlay.Hwnd = CreateWindowEx( NULL, Overlay.Name, Overlay.Name, WS_POPUP | WS_VISIBLE, Process.WindowLeft, Process.WindowTop, Process.WindowWidth, Process.WindowHeight, NULL, NULL, 0, NULL );
	DwmExtendFrameIntoClientArea( Overlay.Hwnd, &DirectX9.Margin );
	SetWindowLong( Overlay.Hwnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW );
	ShowWindow( Overlay.Hwnd, SW_SHOW );
	UpdateWindow( Overlay.Hwnd );
}

std::string RandomString( int len ) {
	srand( time( NULL ) );
	std::string str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	std::string newstr;
	int pos;
	while ( newstr.size( ) != len ) {
		pos = ( ( rand( ) % ( str.size( ) - 1 ) ) );
		newstr += str.substr( pos, 1 );
	}
	return newstr;
}

void better_print( const char *buffer, int colour_id )
{
	HANDLE console = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute( console, colour_id );
	printf( buffer );
}



int main( ) {
	std::filesystem::create_directories( "C:\\rainycheats\\rustc\\Configs" );
	config.run( );
	ShowWindow( GetConsoleWindow( ), SW_SHOW );

	bool WindowFocus = false;
	while ( WindowFocus == false ) {
		DWORD ForegroundWindowProcessID;
		GetWindowThreadProcessId( GetForegroundWindow( ), &ForegroundWindowProcessID );
		if ( get_process_id( TargetProcess ) == ForegroundWindowProcessID ) {
			Process.ID = GetCurrentProcessId( );
			Process.Handle = GetCurrentProcess( );
			Process.Hwnd = GetForegroundWindow( );

			RECT TempRect;
			GetWindowRect( Process.Hwnd, &TempRect );
			Process.WindowWidth = TempRect.right - TempRect.left;
			Process.WindowHeight = TempRect.bottom - TempRect.top;
			Process.WindowLeft = TempRect.left;
			Process.WindowRight = TempRect.right;
			Process.WindowTop = TempRect.top;
			Process.WindowBottom = TempRect.bottom;

			char TempTitle[MAX_PATH];
			GetWindowText( Process.Hwnd, TempTitle, sizeof( TempTitle ) );
			Process.Title = TempTitle;

			char TempClassName[MAX_PATH];
			GetClassName( Process.Hwnd, TempClassName, sizeof( TempClassName ) );
			Process.ClassName = TempClassName;

			char TempPath[MAX_PATH];
			GetModuleFileNameEx( Process.Handle, NULL, TempPath, sizeof( TempPath ) );
			Process.Path = TempPath;

			WindowFocus = true;
		}
	}

	Overlay.Name = RandomString( 10 ).c_str( );
	SetupWindow( );
	DirectXInit( );
	 driver->initialize( get_process_id( "RustClient.exe" ) );
	game_assembly = driver->get_module_base( "GameAssembly.dll" );
	unity_player = driver->get_module_base( "UnityPlayer.dll" );

	std::cout << "game_assembly" << game_assembly << std::endl;
	std::cout << "unity_player" << unity_player << std::endl;

	LoopSetup( );
	MainLoop( );
}