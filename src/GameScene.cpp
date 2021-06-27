#include "GameScene.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"
#include "Sound.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �V���O���g���N���X
const static auto SOUND = Sound::getInst();

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
GameScene::GameScene(IChangeScene* aImpl) : AbstractScene(aImpl)
{
	SOUND->play((int)SoundList::BGM_00);
}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
GameScene::~GameScene()
{
}

//-------------------------------------------------------------------------------------------------
/// �X�V
void GameScene::update()
{
	// �L�����N�^�[
	mPlayer.setTargetPos(mBoss.transform().pos);
	mPlayer.update();	
	mBoss.update();

	// ���[���h�֘A
	mCamera.setPlayerTransform(mPlayer.transform());
	mCamera.setPlayerVelocity(mPlayer.moveVelocity());
	mCamera.update();
	mDirectionalLight.update();
}

//-------------------------------------------------------------------------------------------------
/// �`��
void GameScene::draw()
{
	mPlayer.draw();
	mBoss.draw();
}

//-------------------------------------------------------------------------------------------------
/// �`��2D
void GameScene::draw2D()
{

}

//-------------------------------------------------------------------------------------------------
/// �w�i�`��
void GameScene::drawBackground()
{
	mSkyBox.draw();
}

} // namespace
// EOF
