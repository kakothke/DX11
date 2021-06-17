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
	mRenderer.setSpriteAndShaderData(
		ResourceFileName::Sprite.at(SpriteList::Test),
		ResourceFileName::Shader.at(ShaderList::Sprite)
	);
}

//-------------------------------------------------------------------------------------------------
/// �X�V
void TestSprite::update()
{
	//mTransform.pos.x += 1;
	//mTransform.pos.y += 1;
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
