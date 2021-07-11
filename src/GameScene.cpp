#include "GameScene.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"
#include "Sound.h"

//-------------------------------------------------------------------------------------------------
#include "GameCamera.h"
#include "GameSkyBox.h"
#include "DirectionalLight.h"
#include "Player.h"
#include "StageManager.h"
#include "GameUI.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
const static auto SOUND = Sound::getInst();

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
GameScene::GameScene(IChangeScene* aImpl) : AbstractScene(aImpl)
, mState(GameState::Game)
{
	mGameOBJManager.setCameraObject(new GameCamera());
	mGameOBJManager.setGameObjectListToWorld(new Player());
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
}

//-------------------------------------------------------------------------------------------------
/// 描画
void GameScene::draw()
{
	mGameOBJManager.draw();
}

} // namespace
// EOF
