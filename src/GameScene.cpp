#include "GameScene.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"
#include "Sound.h"
#include "InputManager.h"

//-------------------------------------------------------------------------------------------------
#include "GameCamera.h"
#include "GameSkyBox.h"
#include "DirectionalLight.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
const static auto SOUND = Sound::getInst();
const static auto INPUT_MANAGER = InputManager::getInst();
const static auto FPS = Fps::getInst();

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
GameScene::GameScene(IChangeScene* aImpl) : AbstractScene(aImpl)
, mGameOBJManager()
, mPlayer()
, mStageManager()
, mGameUI()
, mRetryWaitTimer(0.0f)
, mMissFlag(false)
, mRetryFlag(false)
{
	mPlayer = new Player();
	mGameOBJManager.instanceToWorld(mPlayer);
	mStageManager = new StageManager();
	mGameOBJManager.instanceToWorld(mStageManager);
	mGameUI = new GameUI();
	mGameOBJManager.instanceToCanvas(mGameUI);
	mGameOBJManager.instanceToCamera(new GameCamera());
	mGameOBJManager.instanceToWorld(new DirectionalLight());
	mGameOBJManager.instanceToBackground(new GameSkyBox());

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
	mGameUI->setScore(mStageManager->getScore());

	// プレイヤーが非アクティブになったらミスフラグをオン
	if (!mPlayer->activeSelf() && !mMissFlag) {
		mMissFlag = true;
		mGameUI->setMissFlagTrue();
		mStageManager->setMissFlagTrue();
		SOUND->stop((int)SoundList::BGM_00);
	}

	// ミスしていたら
	if (mMissFlag) {
		missEvent();
	}
}

//-------------------------------------------------------------------------------------------------
/// 描画
void GameScene::draw()
{
	mGameOBJManager.draw();
}

//-------------------------------------------------------------------------------------------------
/// ミスイベント
void GameScene::missEvent()
{
	const static float RETRY_WAIT_TIME = 1.5f;

	if (!mRetryFlag) {
		if (INPUT_MANAGER->getButtonDown(InputCode::UP)) {
			// リトライボタンが押された
			mRetryFlag = true;
			SOUND->playOneShot((int)SoundList::SE_Start);
			mRetryWaitTimer = 0.0f;
		}
	} else {
		// リトライ
		if (mRetryWaitTimer > RETRY_WAIT_TIME) {
			mImplSceneChanged->changeScene(SceneList::POP);
		} else {
			mRetryWaitTimer += FPS->deltaTime();
		}
	}
}

} // namespace
// EOF
