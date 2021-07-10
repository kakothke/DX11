#include "SystemMain.h"

//-------------------------------------------------------------------------------------------------
#include "Window.h"
#include "Direct3D11.h"
#include "Input.h"
#include "Sound.h"
#include "Game.h"
#include "Define.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
const static auto WINDOW = Window::getInst();
const static auto D3D11 = Direct3D11::getInst();
const static auto INPUT = Input::getInst();
const static auto SOUND = Sound::getInst();

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
	if (!WINDOW->initialize(Define::WindowName, Define::ResolutionWidth, Define::ResolutionHeight)) {
		return false;
	}
	// Direct3D11������	
	if (!D3D11->initialize()) {
		return false;
	}
	// Input������
	if (!INPUT->initialize()) {
		return false;
	}
	// Sound������
	if (!SOUND->initialize()) {
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
	ShowWindow(WINDOW->hWnd(), SW_SHOW);
	UpdateWindow(WINDOW->hWnd());

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
