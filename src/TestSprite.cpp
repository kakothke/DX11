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
	mRenderer.setSprite(ResourceFileName::Sprite.at(SpriteList::Test));
	mRenderer.setShader(ResourceFileName::Shader.at(ShaderList::Sprite));
	mRenderer.setAnchor(-1, -1);
	mRenderer.setPivot(-1, -1);
}

//-------------------------------------------------------------------------------------------------
/// 更新
void TestSprite::update()
{
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
