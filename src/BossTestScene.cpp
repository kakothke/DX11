#include "BossTestScene.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"
#include "Sound.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
const static auto SOUND = Sound::getInst();

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
BossTestScene::BossTestScene(IChangeScene* aImpl) : AbstractScene(aImpl)
{
	SOUND->play((int)SoundList::BGM_00);

	mGameObjMgr.setCameraObject(new BossCamera());
	mGameObjMgr.instanceToWorld(new TestPlayer());
	mGameObjMgr.instanceToWorld(new Boss());
	mGameObjMgr.instanceToWorld(new DirectionalLight());
	mGameObjMgr.instanceToBackground(new GameSkyBox());
}

//-------------------------------------------------------------------------------------------------
/// デストラクタ
BossTestScene::~BossTestScene()
{
}

//-------------------------------------------------------------------------------------------------
/// 更新
void BossTestScene::update()
{
	mGameObjMgr.update();
}

//-------------------------------------------------------------------------------------------------
/// 描画
void BossTestScene::draw()
{
	mGameObjMgr.draw();
}

} // namespace
// EOF
