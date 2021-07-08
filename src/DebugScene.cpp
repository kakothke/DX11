#include "DebugScene.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"
#include "Sound.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
DebugScene::DebugScene(IChangeScene* aImpl) : AbstractScene(aImpl)
{
	mOBJTest.setOBJ(ResourceFileName::OBJ.at(OBJList::Cube));
	mOBJTest.setShader(ResourceFileName::Shader.at(ShaderList::Standard));

	mSpriteTest.setAnchor(1.0f, 1.0f);
	mSpriteTest.setPivot(1.0f, 1.0f);
	mSpriteTest.setTexture(ResourceFileName::Sprite.at(SpriteList::Test));
	mSpriteTest.setShader(ResourceFileName::Shader.at(ShaderList::Standard));
}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
DebugScene::~DebugScene()
{
}

//-------------------------------------------------------------------------------------------------
/// �X�V
void DebugScene::update()
{
	// ���[���h�֘A
	mCamera.update();
	mDirectionalLight.update();
}

//-------------------------------------------------------------------------------------------------
/// �`��
void DebugScene::draw()
{
	mOBJTest.render(Transform());
	mSpriteTest.render(Transform());
}

//-------------------------------------------------------------------------------------------------
/// �`��2D
void DebugScene::draw2D()
{
}

//-------------------------------------------------------------------------------------------------
/// �w�i�`��
void DebugScene::drawBackground()
{
	mSkyBox.draw();
}

} // namespace
// EOF
