#include "BossTestScene.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"
#include "Sound.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
const static auto D3D11 = Direct3D11::getInst();
const static auto SOUND = Sound::getInst();

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
BossTestScene::BossTestScene(IChangeScene* aImpl) : AbstractScene(aImpl)
{
	SOUND->play((int)SoundList::BGM_00);

	mGameObjMgr.setCameraObject(new BossCamera());
	mGameObjMgr.setGameObjectListToWorld(new TestPlayer());
	mGameObjMgr.setGameObjectListToWorld(new Boss());
	mGameObjMgr.setGameObjectListToWorld(new DirectionalLight());
	mGameObjMgr.setGameObjectListToBackground(new GameSkyBox());
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
