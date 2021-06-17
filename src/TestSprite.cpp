#include "TestSprite.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
TestSprite::TestSprite()
{
	initialize();
}

//-------------------------------------------------------------------------------------------------
/// 引数付きコンストラクタ
TestSprite::TestSprite(Transform aTransform)
{
	mTransform = aTransform;
	initialize();
}

//-------------------------------------------------------------------------------------------------
/// 初期化処理
void TestSprite::initialize()
{
	mRenderer.setSpriteAndShaderData(
		ResourceFileName::Sprite.at(SpriteList::Test),
		ResourceFileName::Shader.at(ShaderList::Sprite)
	);
}

//-------------------------------------------------------------------------------------------------
/// 更新
void TestSprite::update()
{
	//mTransform.pos.x += 1;
	//mTransform.pos.y += 1;
	mTransform.rot += 0.01f;
}

//-------------------------------------------------------------------------------------------------
/// 描画
void TestSprite::draw()
{
	mRenderer.render(mTransform.XMFLOAT3X3());
}

} // namespace
// EOF
