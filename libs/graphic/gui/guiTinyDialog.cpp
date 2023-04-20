#include "guiTinyDialog.h"

char const * TinyDial::guiOpenTextFile() {
    char const * lFilterPatterns[2] = {"*.txt", "*.text"};
    return tinyfd_openFileDialog(
        "Open File", 
        "", 
        2, 
        lFilterPatterns,
        "Text Files",
        0
    );
}
