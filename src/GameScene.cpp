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

	mSpriteTest.setAnchor(1.0f, 1.0f);
	mSpriteTest.setPivot(1.0f, 1.0f);
	mSpriteTest.setTexture(ResourceFileName::Sprite.at(SpriteList::Test));
	mSpriteTest.setShader(ResourceFileName::Shader.at(ShaderList::Sprite));

	mFontTest.setShader(ResourceFileName::Shader.at(ShaderList::Sprite));
	mFontTest.setAnchor(-0.75f, -0.75f);
	mFontTest.setPivot(-1.0f, -1.0f);
	mFontTest.setFont(TEXT("���񂸂����X"));
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
	mSpriteTest.render(Transform());
	mFontTest.draw(TEXT("�e�X�g"), Transform());
}

//-------------------------------------------------------------------------------------------------
/// �w�i�`��
void GameScene::drawBackground()
{
	mSkyBox.draw();
}

} // namespace
// EOF
