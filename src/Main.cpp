#include "SystemMain.h"

//-------------------------------------------------------------------------------------------------
namespace {
KDXK::SystemMain systemMain;
}

//-------------------------------------------------------------------------------------------------
/// �G���g���[�֐�
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	if (systemMain.initialize()) {
		systemMain.msgLoop();
	}

	return 0;
}

// EOF
