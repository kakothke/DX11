#include "Boss.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
Boss::Boss()
{
	// トランスフォーム設定
	mTransform.pos = Vector3(0.0f, 0.0f, 50.0f);

	// タグ
	setTag(GameObjectTag::Boss);

	// 描画設定
	mRenderer.setOBJ(ResourceFileName::OBJ.at(OBJList::Boss));
	mRenderer.setShader(ResourceFileName::Shader.at(ShaderList::Standard));

	mSRenderer.setTexture(ResourceFileName::Sprite.at(SpriteList::UI_Arrow));
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
