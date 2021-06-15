#include "SystemMain.h"

//-------------------------------------------------------------------------------------------------
namespace {
KDXK::SystemMain systemMain;
}

//-------------------------------------------------------------------------------------------------
/// ÉGÉìÉgÉäÅ[ä÷êî
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	if (systemMain.initialize()) {
		systemMain.msgLoop();
	}

	return 0;
}

// EOF
