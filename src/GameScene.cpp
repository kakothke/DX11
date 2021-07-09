#include "GameScene.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"
#include "Sound.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
GameScene::GameScene(IChangeScene* aImpl) : AbstractScene(aImpl)
{
	/*mOBJTest.setOBJ(ResourceFileName::OBJ.at(OBJList::Cube));
	mOBJTest.setShader(ResourceFileName::Shader.at(ShaderList::Standard));
	mSpriteTest.setAnchor(1.0f, 1.0f);
	mSpriteTest.setPivot(1.0f, 1.0f);
	mSpriteTest.setTexture(ResourceFileName::Sprite.at(SpriteList::Test));
	mSpriteTest.setShader(ResourceFileName::Shader.at(ShaderList::Standard));*/
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
	// ���[���h�֘A
	mCamera.update();
	mDirectionalLight.update();

	// �I�u�W�F�N�g
	mPlayer.update();
	mObstractManager.update();
}

//-------------------------------------------------------------------------------------------------
/// �`��
void GameScene::draw()
{
	mPlayer.draw();
	mObstractManager.draw();

	//mOBJTest.render(Transform());
	//mSpriteTest.render(Transform());
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
