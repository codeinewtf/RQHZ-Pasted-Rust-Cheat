#pragma once

#include "XorStr.hpp"
#include "includes.hpp"

#include "function.hpp"
#include <TlHelp32.h>

#define secret_t 166
class c_driver
{
private:
	__int64(__fastcall* function_address)(void*) = nullptr;
	int pid = 0;

	typedef enum _request_codes
	{
		request_base = 0x119,
		request_read = 0x129,
		request_write = 0x139,
		request_pattern = 0x179,
		request_success = 0x91a,
		request_unique = 0x92b,
		request_unload = 0x93c,
		request_rect = 0x117,
		request_text = 0x118,
		request_free = 0x109,
		request_allocate = 0x149,
		request_expose = 0x159,
		request_base86 = 0x187
	}request_codes, * prequest_codes;
	typedef struct _unload_request
	{
		bool* buffer;
	}unload_request, * punload_request;

	typedef struct _rect_request
	{
		uint32_t x;
		uint32_t y;
		uint32_t w;
		uint32_t h;
		uint8_t t;
		uint8_t r;
		uint8_t g;
		uint8_t b;
	}rect_request, * prect_request;

	typedef struct _text_request
	{
		uint32_t x;
		uint32_t y;
		LPCWSTR str;
		uint8_t r;
		uint8_t g;
		uint8_t b;
	}text_request, * ptext_request;


	typedef struct _read_request {
		uint32_t pid;
		uintptr_t address;
		void* buffer;
		size_t size;
	} read_request, * pread_request;

	typedef struct _write_request {
		uint32_t pid;
		uintptr_t address;
		void* buffer;
		size_t size;
	} write_request, * pwrite_request;

	typedef struct _base_request {
		uint32_t pid;
		uintptr_t handle;
		WCHAR name[260];
	} base_request, * pbase_request;

	typedef struct _base_requestx86 {
		int pid;
		uintptr_t handle;
		WCHAR name[260];
	} base_requestx86, * p_base_request;
	typedef struct _pattern_request
	{
		int pid;
		uintptr_t base;
		char signature[260];
		uintptr_t address;
	}pattern_request, * ppattern_request;

	typedef struct _request_data
	{
		uint32_t unique;
		request_codes code;
		void* data;
	}request_data, * prequest_data;

public:

	auto initialize(const int process_id) -> bool
	{
		pid = process_id;

		LoadLibrary(("user32.dll"));

		const auto win32k = LoadLibrary(("win32u.dll"));

		if (!win32k)
		{
			return false;
		}

		*(void**)&function_address = GetProcAddress(win32k, ("NtUserAutoRotateScreen"));

		if (!function_address)
		{
			return false;
		}

		return true;
	}



	auto send_cmd(void* data, request_codes code) -> bool
	{
		if (!data || !code)
		{
			return false;
		}

		request_data request{ 0 };

		request.unique = request_unique;
		request.data = data;
		request.code = code;

		const auto result = function_address(&request);

		if (result != request_success)
		{
			return false;
		}

		return true;
	}

	auto draw_rect(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint8_t t, uint8_t r, uint8_t g, uint8_t b) -> const std::uintptr_t
	{
		_rect_request data{ };
		data.x = x;
		data.y = y;
		data.w = w;
		data.h = h;
		data.t = t;
		data.r = r;
		data.g = g;
		data.b = b;

		return send_cmd(&data, request_rect);
	}

	auto draw_text(uint32_t x, uint32_t y, const wchar_t* str, uint8_t r, uint8_t g, uint8_t b) -> const std::uintptr_t
	{
		_text_request data{ };
		data.x = x;
		data.y = y;
		data.str = str;
		data.r = r;
		data.g = g;
		data.b = b;

		return send_cmd(&data, request_text);
	}

	auto get_module_base(const std::string module_name) -> const std::uintptr_t
	{
		base_request data{ 0 };

		data.pid = pid;
		data.handle = 0;

		std::wstring wstr = std::wstring(module_name.begin(), module_name.end());

		memset(data.name, 0, sizeof(WCHAR) * 260);
		wcscpy(data.name, wstr.c_str());

		send_cmd(&data, request_base);

		return data.handle;
	}

	auto get_module_base_x86(const std::string module_name) -> const std::uintptr_t
	{
		base_requestx86 data{ 0 };

		data.pid = pid;
		data.handle = 0;

		std::wstring wstr = std::wstring(module_name.begin(), module_name.end());

		memset(data.name, 0, sizeof(WCHAR) * 260);
		wcscpy(data.name, wstr.c_str());

		send_cmd(&data, request_base86);

		return data.handle;
	}

	auto find_signature(const std::uintptr_t base, const std::string signature) -> std::uintptr_t
	{
		pattern_request data{ 0 };

		data.pid = pid;
		data.base = base;
		data.address = 0;

		memset(data.signature, 0, sizeof(char) * 260);
		strcpy(data.signature, signature.c_str());

		send_cmd(&data, request_pattern);

		return data.address;
	}

	auto read(const std::uintptr_t address, void* buffer, const std::size_t size) -> bool
	{
		read_request data{ 0 };

		data.pid = pid;
		data.address = address;
		data.buffer = buffer;
		data.size = size;

		return send_cmd(&data, request_read);
	}

	template <typename t>
	auto read(const std::uintptr_t address) -> t
	{
		t response{ };
		this->read(address, &response, sizeof(t));
		return response;
	}

	template<typename t>
	auto read_chain(const std::uintptr_t address, const std::vector<std::uintptr_t> chain) -> t
	{
		auto current = address;

		for (int i = 0; i < chain.size() - 1; i++)
		{
			current = this->read<std::uintptr_t>(current + chain[i]);
		}
		return this->read<t>(current + chain[chain.size() - 1]);
	};

	auto write(const std::uintptr_t address, void* buffer, const std::size_t size) -> bool
	{
		write_request data{ 0 };

		data.pid = pid;
		data.address = address;
		data.buffer = buffer;
		data.size = size;

		return send_cmd(&data, request_write);
	}

	template <typename t>
	auto write(const std::uintptr_t address, t value) -> bool
	{
		return this->write(address, &value, sizeof(t));
	}

	auto unload() -> bool
	{
		unload_request data{ 0 };

		bool buffer = false;

		data.buffer = &buffer;

		const auto result = send_cmd(&data, request_unload);

		if (!result || !buffer)
		{
			return false;
		}

		return true;
	}


	std::wstring read_string(uintptr_t address)
	{
		wchar_t buffer[1024 * sizeof(wchar_t)];
		read(address, &buffer, 1024 * sizeof(wchar_t));

		std::wstring new_buffer = std::wstring(buffer);

		return new_buffer;
	}

	std::string read_wstr(uintptr_t address)
	{
		wchar_t buffer[1024 * sizeof(wchar_t)];
		read(address, &buffer, 1024 * sizeof(wchar_t));

		std::wstring new_buffer = std::wstring(buffer);

		return std::string(new_buffer.begin(), new_buffer.end());
	}
};
static c_driver* driver = new c_driver();
