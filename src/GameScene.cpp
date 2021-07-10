#include "GameScene.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"
#include "Sound.h"

//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
GameScene::GameScene(IChangeScene* aImpl) : AbstractScene(aImpl)
, mState(GameState::Game)
{
	mPlayer = new Player();
	mGameOBJManager.setGameObjectListToWorld(mPlayer);
	mGameOBJManager.setGameObjectListToWorld(new DirectionalLight());
	mGameOBJManager.setGameObjectListToWorld(new ObstractManager());
	mGameOBJManager.setGameObjectListToBackground(new GameSkyBox());
	mCamera = new GameCamera();
	mGameOBJManager.setCameraObject(mCamera);
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
	mCamera->setPlayerPos(mPlayer->transform().pos);
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
