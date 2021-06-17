#include "SystemMain.h"

//-------------------------------------------------------------------------------------------------
#include "Window.h"
#include "Direct3D11.h"
#include "Game.h"
#include "Define.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
SystemMain::SystemMain()
{
}

//-------------------------------------------------------------------------------------------------
/// ����������
/// @return ���������� ����(true)
bool SystemMain::initialize()
{
	// �E�B���h�E������
	const auto window = Window::getInst();
	if (!window->initialize(Define::WindowName, Define::ResolutionWidth, Define::ResolutionHeight)) {
		return false;
	}
	// Direct3D11������
	const auto d3d11 = Direct3D11::getInst();
	if (!d3d11->initialize()) {
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// ���b�Z�[�W���[�v
void SystemMain::msgLoop()
{
	// �Q�[��������
	Game game;
	if (!game.initialize()) {
		return;
	}

	// �E�B���h�E��\��
	{
		const auto hWnd = Window::getInst()->hWnd();
		ShowWindow(hWnd, SW_SHOW);
		UpdateWindow(hWnd);
	}

	// ���b�Z�[�W���[�v
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
