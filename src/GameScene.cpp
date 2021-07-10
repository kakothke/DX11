#include "GameScene.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"
#include "Sound.h"

//-------------------------------------------------------------------------------------------------
#include "GameCamera.h"
#include "GameSkyBox.h"
#include "DirectionalLight.h"
#include "Player.h"
#include "ObstractManager.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
GameScene::GameScene(IChangeScene* aImpl) : AbstractScene(aImpl)
, mState(GameState::Game)
{
	mGameOBJManager.setGameObjectListToWorld(new Player());
	mGameOBJManager.setGameObjectListToWorld(new DirectionalLight());
	mGameOBJManager.setGameObjectListToWorld(new ObstractManager());
	mGameOBJManager.setGameObjectListToBackground(new GameSkyBox());
	mGameOBJManager.setCameraObject(new GameCamera());
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
}

//-------------------------------------------------------------------------------------------------
/// �`��
void GameScene::draw()
{
	mGameOBJManager.draw();
}

} // namespace
// EOF
