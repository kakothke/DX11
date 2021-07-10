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
	mPlayer = std::make_shared<Player>();
	mGameOBJManager.setGameObjectListToWorld(mPlayer);
	mCamera = std::make_shared<GameCamera>();
	mGameOBJManager.setCameraObject(mCamera);
	mGameOBJManager.setGameObjectListToWorld(std::make_shared<DirectionalLight>());
	mGameOBJManager.setGameObjectListToWorld(std::make_shared<ObstractManager>());
	mGameOBJManager.setGameObjectListToBackground(std::make_shared<GameSkyBox>());
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
