#include "guiTinyDialog.h"

wchar_t const * TinyDial::guiOpenTextFile() {
    return tinyfd_openFileDialogW(L"Open File", L"", 0, {}, L"", 0);
}
