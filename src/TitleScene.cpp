#include "TitleScene.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"
#include "Sound.h"
#include "InputManager.h"

//-------------------------------------------------------------------------------------------------
#include "TitleCamera.h"
#include "GameSkyBox.h"
#include "DirectionalLight.h"
#include "Player.h"
#include "TitleUI.h"
#include "TitlePlayer.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
const static auto SOUND = Sound::getInst();
const static auto INPUT_MANAGER = InputManager::getInst();
const static auto FPS = Fps::getInst();

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
TitleScene::TitleScene(IChangeScene* aImpl) : AbstractScene(aImpl)
, mGameOBJManager()
, mSceneChangeWaitTimer(0.0f)
, mStartFlag(false)
{
	mGameOBJManager.instanceToCamera(new TitleCamera());
	mGameOBJManager.instanceToWorld(new DirectionalLight());
	mGameOBJManager.instanceToBackground(new GameSkyBox());
	mGameOBJManager.instanceToWorld(new TitlePlayer());
	mGameOBJManager.instanceToCanvas(new TitleUI());
}

//-------------------------------------------------------------------------------------------------
/// デストラクタ
TitleScene::~TitleScene()
{
}

//-------------------------------------------------------------------------------------------------
/// 更新
void TitleScene::update()
{
	const static float SCENE_CHANGE__WAIT_TIME = 1.5f;

	mGameOBJManager.update();

	// スタート処理
	if (!mStartFlag) {
		if (INPUT_MANAGER->getButtonDown(InputCode::UP)) {
			// スタートボタンが押された
			mStartFlag = true;
			SOUND->playOneShot((int)SoundList::SE_Start);
			mSceneChangeWaitTimer = 0.0f;
		}
	} else {
		// シーン移動
		if (mSceneChangeWaitTimer > SCENE_CHANGE__WAIT_TIME) {
			mImplSceneChanged->changeScene(SceneList::Game);
		} else {
			mSceneChangeWaitTimer += FPS->deltaTime();
		}
	}
}

//-------------------------------------------------------------------------------------------------
/// 描画
void TitleScene::draw()
{
	mGameOBJManager.draw();
}

} // namespace
// EOF
