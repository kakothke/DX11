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
