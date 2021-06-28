#include "PlayerBullet.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// 定数
const static float DEFINE_ACTIVE_TIME = 1.0f;
const static float DEFINE_BULLET_SPEED = 2.0f;

//-------------------------------------------------------------------------------------------------
/// シングルトンクラス
const static auto FPS = Fps::getInst();

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
PlayerBullet::PlayerBullet(Transform aTransform, Vector3 aTargetPos)
	: mRenderer()
	, mVelocity(aTargetPos - aTransform.pos)
	, mTimer(0)
{
	// 生成位置
	mTransform = aTransform;
	mTransform.scale = 0.25f;
	mTransform.scale.z = 1.0f;

	// 描画設定
	//mRenderer.setTexture(ResourceFileName::Sprite.at(SpriteList::Test));
	mRenderer.setShader(ResourceFileName::Shader.at(ShaderList::Standard));
	mRenderer.setOBJ(ResourceFileName::OBJ.at(OBJList::Player));
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
	mTransform.pos += mVelocity.Normalized() * DEFINE_BULLET_SPEED;

	// 一定時間たったら消す
	if (mTimer > DEFINE_ACTIVE_TIME) {
		setActive(false);
	}
	mTimer += FPS->deltaTime();
}

//-------------------------------------------------------------------------------------------------
/// 描画
void PlayerBullet::draw()
{
	mRenderer.render(mTransform);
}

} // namespace
// EOF
