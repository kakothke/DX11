#include "SystemMain.h"

//-------------------------------------------------------------------------------------------------
#include "Window.h"
#include "Direct3D11.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
SystemMain::SystemMain()
{
}

//-------------------------------------------------------------------------------------------------
/// ����������
bool SystemMain::initialize() const
{
	// �E�B���h�E������
	if (!Window::getInst()->initialize()) {
		return false;
	}
	// Direct3D11������
	if (!Direct3D11::getInst()->initialize()) {
		return false;
	}

	// �E�B���h�E��\��
	ShowWindow(Window::getInst()->hWnd(), SW_SHOW);
	UpdateWindow(Window::getInst()->hWnd());

	return true;
}

//-------------------------------------------------------------------------------------------------
/// ���b�Z�[�W���[�v
void SystemMain::msgLoop()
{
	Game game;
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
