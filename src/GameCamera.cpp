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
	// プレイヤーを親オブジェクトとして連動させる
	mTransform = mPlayerTransform;
	mTransform.localPos = -mPlayerVelocity;
	mTransform.localPos.z = -mDistanceFromPlayer;

	// コンスタントバッファ更新
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
