#include "Boss.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// 定数
const static Vector3 DEFINE_POS = Vector3(0.0f, 0.0f, 50.0f);

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
Boss::Boss()
{
	// 初期位置
	mTransform.pos = DEFINE_POS;
	//mTransform.scale = 100;

	// 描画設定
	mRenderer.setOBJ(ResourceFileName::OBJ.at(OBJList::Boss));
	mRenderer.setShader(ResourceFileName::Shader.at(ShaderList::Standard));

	mSRenderer.setTexture(ResourceFileName::Sprite.at(SpriteList::Test));
	mSRenderer.setShader(ResourceFileName::Shader.at(ShaderList::Unlit));
}

//-------------------------------------------------------------------------------------------------
/// 更新
void Boss::update()
{
}

//-------------------------------------------------------------------------------------------------
/// 描画
void Boss::draw()
{
	mRenderer.render(mTransform);
	mSRenderer.render(mTransform);
}

} // namespace
// EOF
