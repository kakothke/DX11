#include "TestSprite.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "Define.h"
#include "ResourceFileName.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

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
		ResourceFileName::Shader.at(ShaderList::Standard)
	);
	mTransform.pos.x = 3;
}

//-------------------------------------------------------------------------------------------------
/// �X�V
void TestSprite::update()
{
	mTransform.rot.y += 0.01f;
}

//-------------------------------------------------------------------------------------------------
/// �`��
void TestSprite::draw()
{
	mRenderer.render(mTransform);
}

} // namespace
// EOF
