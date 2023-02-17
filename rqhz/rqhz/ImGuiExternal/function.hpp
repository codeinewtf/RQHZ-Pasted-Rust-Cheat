#pragma once

#include "XorStr.hpp"
#include "includes.hpp"

#include "controller.hpp"

enum control
{
    read = 444,
    write = 555,
    base = 666,
};

struct cmd_t
{
    /* driver instructions */
    DWORD key;
    control code;

    /* parameters */
    DWORD process_id;

    /* module base */
    PVOID outbase;
    wchar_t* module_name;

    /* read/write */
    PVOID address;
    PVOID value;
    size_t size;
};

class function_t
{
private:
    int64_t(__fastcall* call_driver)(PVOID a1, PVOID a2, PVOID a3, PVOID a4, PVOID a5, PVOID a6);
public:
    bool setup()
    {
        HMODULE user32 = LoadLibraryA(_("user32.dll").c_str());
        HMODULE win32u = LoadLibraryA(_("win32u.dll").c_str());

        *(PVOID*)&call_driver = GetProcAddress(win32u, _("NtUserCreateDesktopEx").c_str());

        return call_driver;
    }

    void call(cmd_t* cmd)
    {
        call_driver(cmd, 0, 0, 0, 0, 0);
    }
}function;
