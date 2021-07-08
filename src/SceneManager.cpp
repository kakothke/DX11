#include "SceneManager.h"

//-------------------------------------------------------------------------------------------------
#include <Windows.h>
#include "Direct3D11.h"

//-------------------------------------------------------------------------------------------------
#include "GameScene.h"
#include "BossTestScene.h"
#include "DebugScene.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �V���O���g���N���X
const static auto D3D11 = Direct3D11::getInst();

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
SceneManager::SceneManager()
	: mSceneStack()
{
}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
SceneManager::~SceneManager()
{
	// �V�[���̃X�^�b�N��S���|�b�v����
	while (!mSceneStack.empty()) {
		mSceneStack.pop();
	}
}

//-------------------------------------------------------------------------------------------------
/// �X�V
void SceneManager::update()
{
	if (!mSceneStack.empty()) {
		mSceneStack.top()->update();
	}
}

//-------------------------------------------------------------------------------------------------
/// �`��
void SceneManager::draw()
{
	if (!mSceneStack.empty()) {
		// �w�i
		D3D11->setZBufferMode(0);
		D3D11->setBlendMode(BlendList::Normal);
		mSceneStack.top()->drawBackground();

		// ���[���h
		D3D11->setZBufferMode(1);
		D3D11->setBlendMode(BlendList::None);
		mSceneStack.top()->draw();

		// �X�N���[��
		D3D11->setZBufferMode(0);
		D3D11->setBlendMode(BlendList::Normal);
		mSceneStack.top()->draw2D();
	}
}

//-------------------------------------------------------------------------------------------------
/// �V�[���J��
/// @param aSceneList �؂�ւ���V�[�����w�肷��\����
void SceneManager::changeScene(const SceneList aSceneList)
{
	switch (aSceneList) {
	case SceneList::POP:
		// ���݂̃V�[�����|�b�v����
		mSceneStack.pop();
		break;
	case SceneList::Game:
		mSceneStack.push(std::make_shared<GameScene>(this));
		break;
	case SceneList::BossTest:
		mSceneStack.push(std::make_shared<BossTestScene>(this));
		break;
	case SceneList::Debug:
		mSceneStack.push(std::make_shared<DebugScene>(this));
		break;
	default:
		// �G���[���b�Z�[�W
		MessageBox(nullptr, TEXT("�ǂݍ������Ƃ����V�[�������݂��܂���B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
	}
}

} // namespace
// EOF
