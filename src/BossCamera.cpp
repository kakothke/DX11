#include "BossCamera.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// 定数
const static float DEFINE_DISTANCE = 20.0f;

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
BossCamera::BossCamera()
	: mLocalTransform()
	, mPlayerTransform()
	, mPlayerVelocity()
	, mDistanceFromPlayer(DEFINE_DISTANCE)
{
}

//-------------------------------------------------------------------------------------------------
/// 更新
void BossCamera::update()
{
	// プレイヤーを親オブジェクトとして連動させる
	mTransform = mPlayerTransform;
	mTransform.localPos = -mPlayerVelocity;
	mTransform.localPos.z = -mDistanceFromPlayer;

	// コンスタントバッファ更新
	updateConstantBuffer();
}

//-------------------------------------------------------------------------------------------------
/// 描画
void BossCamera::draw()
{
}

//-------------------------------------------------------------------------------------------------
/// プレイヤーのトランスフォームを設定する
/// @param aTransform トランスフォーム
void BossCamera::setPlayerTransform(const Transform& aTransform)
{
	mPlayerTransform = aTransform;
}

//-------------------------------------------------------------------------------------------------
/// プレイヤーの移動速度を設定する
/// @param aVelocity 
void BossCamera::setPlayerVelocity(const Vector2& aVelocity)
{
	mPlayerVelocity = aVelocity;
}

} // namespace
// EOF
