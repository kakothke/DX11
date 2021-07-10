#include "GameScene.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"
#include "Sound.h"

//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
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
/// デストラクタ
GameScene::~GameScene()
{
}

//-------------------------------------------------------------------------------------------------
/// 更新
void GameScene::update()
{
	mCamera->setPlayerPos(mPlayer->transform().pos);
	mGameOBJManager.update();
}

//-------------------------------------------------------------------------------------------------
/// 描画
void GameScene::draw()
{
	mGameOBJManager.draw();
}

} // namespace
// EOF
