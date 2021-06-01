#include "TestSprite.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"
#include "Define.h"
#include "ResourceFileName.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

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
		ResourceFileName::Shader.at(ShaderList::Standard)
	);
	mTransform.pos.x = 3;
}

//-------------------------------------------------------------------------------------------------
/// 更新
void TestSprite::update()
{
	mTransform.rot.y += 0.01f;
}

//-------------------------------------------------------------------------------------------------
/// 描画
void TestSprite::draw()
{
	mRenderer.render(mTransform);
}

} // namespace
// EOF
