#include "BossTestScene.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"
#include "Sound.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
const static auto SOUND = Sound::getInst();

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
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
/// �f�X�g���N�^
BossTestScene::~BossTestScene()
{
}

//-------------------------------------------------------------------------------------------------
/// �X�V
void BossTestScene::update()
{
	mGameObjMgr.update();
}

//-------------------------------------------------------------------------------------------------
/// �`��
void BossTestScene::draw()
{
	mGameObjMgr.draw();
}

} // namespace
// EOF
