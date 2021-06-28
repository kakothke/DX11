#include "PlayerBullet.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
PlayerBullet::PlayerBullet()
{
	mRenderer.setTexture(ResourceFileName::Sprite.at(SpriteList::Test));
	mRenderer.setShader(ResourceFileName::Shader.at(ShaderList::Standard));
}

//-------------------------------------------------------------------------------------------------
/// デストラクタ
PlayerBullet::~PlayerBullet()
{
}

//-------------------------------------------------------------------------------------------------
/// 更新
void PlayerBullet::update()
{

}

//-------------------------------------------------------------------------------------------------
/// 描画
void PlayerBullet::draw()
{
	mRenderer.render(mTransform);
}

} // namespace
// EOF
