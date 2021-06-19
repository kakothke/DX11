#include "TestSprite.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
TestSprite::TestSprite()
{
	initialize();
}

//-------------------------------------------------------------------------------------------------
/// �����t���R���X�g���N�^
TestSprite::TestSprite(Transform aTransform)
{
	mTransform = aTransform;
	initialize();
}

//-------------------------------------------------------------------------------------------------
/// ����������
void TestSprite::initialize()
{
	mRenderer.setSprite(ResourceFileName::Sprite.at(SpriteList::Test));
	mRenderer.setShader(ResourceFileName::Shader.at(ShaderList::Sprite));
	mRenderer.setAnchor(-1, -1);
	mRenderer.setPivot(-1, -1);
}

//-------------------------------------------------------------------------------------------------
/// �X�V
void TestSprite::update()
{
	mTransform.rot += 0.01f;
}

//-------------------------------------------------------------------------------------------------
/// �`��
void TestSprite::draw()
{
	mRenderer.render(mTransform.XMFLOAT3X3());
}

} // namespace
// EOF
