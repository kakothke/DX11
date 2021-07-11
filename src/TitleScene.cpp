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
{
	mGameOBJManager.setCameraObject(new TitleCamera());
	mGameOBJManager.setGameObjectListToWorld(new DirectionalLight());
	mGameOBJManager.setGameObjectListToBackground(new GameSkyBox());
	mGameOBJManager.setGameObjectListToWorld(new TitlePlayer());
	mGameOBJManager.setGameObjectListToCanvas(new TitleUI());
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
	mGameOBJManager.update();

	static bool startButtonDown;
	if (!startButtonDown) {
		if (INPUT_MANAGER->axesRaw().y == 1) {
			startButtonDown = true;
			SOUND->playOneShot((int)SoundList::SE_Start);
		}
	} else {
		const static float SCENE_CHANGE_TIME = 1.5f;
		static float sceneChangeTimer = 0;
		if (sceneChangeTimer > SCENE_CHANGE_TIME) {
			mImplSceneChanged->changeScene(SceneList::Game);
		}
		sceneChangeTimer += FPS->deltaTime();
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
