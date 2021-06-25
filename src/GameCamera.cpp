#include "GameCamera.h"

//-------------------------------------------------------------------------------------------------
#include "Direct3D11.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
GameCamera::GameCamera()
	: mLocalTransform()
	, mPlayerTransform()
	, mDirectionFromPlayer(30.0f)
{
	mTransform.pos.z = 50;
}

//-------------------------------------------------------------------------------------------------
/// 更新
void GameCamera::update()
{
	// ローカル位置を設定
	mLocalTransform.pos.z = -mDirectionFromPlayer;

	// プレイヤーを親オブジェクトとして連動させる
	DirectX::XMMATRIX transform = mLocalTransform.worldMatrix() * mPlayerTransform.worldMatrix();
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
/// プレイヤーのトランスフォームを取得する
/// @param aTransform トランスフォーム
void GameCamera::setPlayerTransform(const Transform& aTransform)
{
	mPlayerTransform = aTransform;
}

} // namespace
// EOF
