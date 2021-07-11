#include "SceneManager.h"

//-------------------------------------------------------------------------------------------------
#include "TitleScene.h"
#include "GameScene.h"
#include "BossTestScene.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

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
		mSceneStack.top()->draw();
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
	case SceneList::Title:
		mSceneStack.push(std::make_shared<TitleScene>(this));
		break;
	case SceneList::Game:
		mSceneStack.push(std::make_shared<GameScene>(this));
		break;
	case SceneList::BossTest:
		mSceneStack.push(std::make_shared<BossTestScene>(this));
		break;
	default:
		// �G���[���b�Z�[�W
		MessageBox(nullptr, TEXT("�ǂݍ������Ƃ����V�[�������݂��܂���B"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
	}
}

} // namespace
// EOF
