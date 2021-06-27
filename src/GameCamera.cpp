#include "GameCamera.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// 定数
const static float DEFINE_DISTANCE = 20.0f;

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
GameCamera::GameCamera()
	: mLocalTransform()
	, mPlayerTransform()
	, mPlayerVelocity()
	, mDistanceFromPlayer(DEFINE_DISTANCE)
{
}

//-------------------------------------------------------------------------------------------------
/// 更新
void GameCamera::update()
{
	// ローカル位置を設定
	mLocalTransform.pos = -mPlayerVelocity;
	mLocalTransform.pos.z = -mDistanceFromPlayer;

	// プレイヤーを親オブジェクトとして連動させる
	DirectX::XMMATRIX transform = mLocalTransform.WorldMatrix() * mPlayerTransform.WorldMatrix();
	mTransform.pos.x = transform.r[3].m128_f32[0];
	mTransform.pos.y = transform.r[3].m128_f32[1];
	mTransform.pos.z = transform.r[3].m128_f32[2];
	mTransform.rot = -mPlayerTransform.rot;

	updateConstantBuffer();
}

//-------------------------------------------------------------------------------------------------
/// 描画
void GameCamera::draw()
{
}

//-------------------------------------------------------------------------------------------------
/// プレイヤーのトランスフォームを設定する
/// @param aTransform トランスフォーム
void GameCamera::setPlayerTransform(const Transform& aTransform)
{
	mPlayerTransform = aTransform;
}

//-------------------------------------------------------------------------------------------------
/// プレイヤーの移動速度を設定する
/// @param aVelocity 
void GameCamera::setPlayerVelocity(const Vector2& aVelocity)
{
	mPlayerVelocity = aVelocity;
}

} // namespace
// EOF
