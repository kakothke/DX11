#include "BossTestScene.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"
#include "Sound.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �V���O���g���N���X
const static auto D3D11 = Direct3D11::getInst();
const static auto SOUND = Sound::getInst();

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
BossTestScene::BossTestScene(IChangeScene* aImpl) : AbstractScene(aImpl)
{
	SOUND->play((int)SoundList::BGM_00);

	mCamera = std::make_shared<BossCamera>();
	mGameObjMgr.setCameraObject(mCamera);
	mPlayer = std::make_shared<TestPlayer>();
	mGameObjMgr.setGameObjectListToWorld(mPlayer);
	mBoss = std::make_shared<Boss>();
	mGameObjMgr.setGameObjectListToWorld(mBoss);
	mGameObjMgr.setGameObjectListToWorld(std::make_shared<DirectionalLight>());
	mGameObjMgr.setGameObjectListToBackground(std::make_shared<GameSkyBox>());

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
	mGameObjMgr.update();
	mPlayer->setTargetPos(mBoss->transform().pos);
	mCamera->setPlayerTransform(mPlayer->transform());
	mCamera->setPlayerVelocity(mPlayer->moveVelocity());
}

//-------------------------------------------------------------------------------------------------
/// �`��
void BossTestScene::draw()
{
	mGameObjMgr.draw();

	D3D11->setZBuffer(false);
	D3D11->setBlendMode(Direct3D11::BlendList::Normal);
	static Transform sptmp;
	sptmp.rot *= Quaternion::Euler(Vector3::up);
	mSpriteTest.render(sptmp);
	mFontTest.draw(TEXT("�t�H���g �`��e�X�g"), Transform(Vector3(), Vector3(), Vector3(0.5f)));
}

} // namespace
// EOF
