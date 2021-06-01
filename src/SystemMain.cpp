#include "SystemMain.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "Game.h"
#include "OBJLoader.h"
#include "OBJFileName.h"
#include "ShaderLoader.h"
#include "ShaderFileName.h"
#include "SpriteLoader.h"
#include "SpriteFileName.h"

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

	// Singleton�N���X���p�����Ă���N���X�̎��̉�
	OBJLoader::getInst();
	ShaderLoader::getInst();
	SpriteLoader::getInst();

	// ���\�[�X�̓ǂݍ���
	OBJLoader::getInst()->load(OBJFileName::fileName(OBJList::Cube));
	OBJLoader::getInst()->load(OBJFileName::fileName(OBJList::Sphere));
	OBJLoader::getInst()->load(OBJFileName::fileName(OBJList::TestObj));
	ShaderLoader::getInst()->load(ShaderFileName::fileName(ShaderList::Unlit));
	ShaderLoader::getInst()->load(ShaderFileName::fileName(ShaderList::Standard));
	ShaderLoader::getInst()->load(ShaderFileName::fileName(ShaderList::Sprite));
	SpriteLoader::getInst()->load(SpriteFileName::fileName(SpriteList::TestTexture));

	// �E�B���h�E��\��
	ShowWindow(mWindow.hWnd(), SW_SHOW);
	UpdateWindow(mWindow.hWnd());

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
