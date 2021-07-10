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
	mPlayer = new Player();
	mGameOBJManager.setGameObjectListToWorld(mPlayer);
	mGameOBJManager.setGameObjectListToWorld(new DirectionalLight());
	mGameOBJManager.setGameObjectListToWorld(new ObstractManager());
	mGameOBJManager.setGameObjectListToBackground(new GameSkyBox());
	mCamera = new GameCamera();
	mGameOBJManager.setCameraObject(mCamera);
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
