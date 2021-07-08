#include "BossTestScene.h"

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
BossTestScene::BossTestScene(IChangeScene* aImpl) : AbstractScene(aImpl)
{
	SOUND->play((int)SoundList::BGM_00);

	mSpriteTest.setAnchor(1.0f, 1.0f);
	mSpriteTest.setPivot(1.0f, 1.0f);
	mSpriteTest.setTexture(ResourceFileName::Sprite.at(SpriteList::Test));
	mSpriteTest.setShader(ResourceFileName::Shader.at(ShaderList::Sprite));

	mFontTest.setShader(ResourceFileName::Shader.at(ShaderList::Sprite));
	mFontTest.setAnchor(-0.5f, -0.9f);
	mFontTest.setPivot(-1.0f, -1.0f);
	mFontTest.setFont(TEXT("���񂸂����X"));
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
void BossTestScene::draw()
{
	mPlayer.draw();
	mBoss.draw();
}

//-------------------------------------------------------------------------------------------------
/// �`��2D
void BossTestScene::draw2D()
{
	static Transform sptmp;
	sptmp.rot *= Quaternion::Euler(Vector3::up);
	mSpriteTest.render(sptmp);
	mFontTest.draw(TEXT("�t�H���g �`��e�X�g"), Transform(Vector3(), Vector3(), Vector3(0.5f)));
}

//-------------------------------------------------------------------------------------------------
/// �w�i�`��
void BossTestScene::drawBackground()
{
	mSkyBox.draw();
}

} // namespace
// EOF
