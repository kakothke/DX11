#include "GameScene.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"
#include "Sound.h"

//-------------------------------------------------------------------------------------------------
#include "GameCamera.h"
#include "GameSkyBox.h"
#include "DirectionalLight.h"
#include "StageManager.h"
#include "GameUI.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
const static auto SOUND = Sound::getInst();

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
GameScene::GameScene(IChangeScene* aImpl) : AbstractScene(aImpl)
{
	mPlayer = new Player();
	mGameOBJManager.setCameraObject(new GameCamera());
	mGameOBJManager.instanceToWorld(mPlayer);
	mGameOBJManager.instanceToWorld(new DirectionalLight());
	mGameOBJManager.instanceToWorld(new StageManager());
	mGameOBJManager.instanceToBackground(new GameSkyBox());
	mGameOBJManager.instanceToCanvas(new GameUI());

	SOUND->play((int)SoundList::BGM_00);
}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
GameScene::~GameScene()
{
}

//-------------------------------------------------------------------------------------------------
/// �X�V
void GameScene::update()
{
	mGameOBJManager.update();

	if (!mPlayer->activeSelf()) {
		SOUND->stop((int)SoundList::BGM_00);
	}
}

//-------------------------------------------------------------------------------------------------
/// �`��
void GameScene::draw()
{
	mGameOBJManager.draw();
}

} // namespace
// EOF
