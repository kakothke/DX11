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
/// コンストラクタ
GameScene::GameScene(IChangeScene* aImpl) : AbstractScene(aImpl)
{
	mPlayer = new Player();
	mGameOBJManager.setCameraObject(new GameCamera());
	mGameOBJManager.setGameObjectListToWorld(mPlayer);
	mGameOBJManager.setGameObjectListToWorld(new DirectionalLight());
	mGameOBJManager.setGameObjectListToWorld(new StageManager());
	mGameOBJManager.setGameObjectListToBackground(new GameSkyBox());
	mGameOBJManager.setGameObjectListToCanvas(new GameUI());

	SOUND->play((int)SoundList::BGM_00);
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
	mGameOBJManager.update();

	if (!mPlayer->activeSelf()) {
		SOUND->stop((int)SoundList::BGM_00);
	}
}

//-------------------------------------------------------------------------------------------------
/// 描画
void GameScene::draw()
{
	mGameOBJManager.draw();
}

} // namespace
// EOF
