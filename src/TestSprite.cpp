#include "TestSprite.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "Define.h"
#include "SpriteFileName.h"
#include "ShaderFileName.h"

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
		SpriteFileName::fileName(SpriteList::TestTexture),
		ShaderFileName::fileName(ShaderList::Standard)
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
