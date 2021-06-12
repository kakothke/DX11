#include "SystemMain.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "Game.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
SystemMain::SystemMain()
	: mWindow()
{
}

//-------------------------------------------------------------------------------------------------
/// ����������
/// @return ���������� ����(true)
bool SystemMain::initialize()
{
	// �E�B���h�E������
	if (!mWindow.initialize()) {
		return false;
	}
	// Direct3D11������
	if (!Direct3D11::getInst()->initialize()) {
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// ���b�Z�[�W���[�v
void SystemMain::msgLoop()
{
	Game game;
	if (!game.initialize()) {
		return;
	}

	// �E�B���h�E��\��
	ShowWindow(mWindow.hWnd(), SW_SHOW);
	UpdateWindow(mWindow.hWnd());

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			// OS����̃��b�Z�[�W���E�B���h�E�v���V�[�W���[�ɓn��
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} else {
			// �Q�[���̃��C�����[�v
			if (!game.mainLoop()) {
				break;
			}
		}
	}
}

} // namespace
// EOF
