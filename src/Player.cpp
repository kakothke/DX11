#include "Player.h"

//-------------------------------------------------------------------------------------------------
#include "MyOutputDebugString.h" 
#include "ResourceFileName.h"
#include "InputManager.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
static const float MOVE_SPEED = 0.05f;

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
Player::Player()
{
	initialize();
	mTransform.scale.x = 0.5f;
	mTransform.scale.y = 0.5f;
	mTransform.scale.z = 2;
}

//-------------------------------------------------------------------------------------------------
/// 初期化処理
void Player::initialize()
{
	// 描画設定
	mRenderer.setOBJ(ResourceFileName::OBJ.at(OBJList::Player));
	mRenderer.setShader(ResourceFileName::Shader.at(ShaderList::Standard));

	// 初期設定
	mDistanceFromBoss = 100;
	mPoseMat = DirectX::XMMatrixIdentity();
}

//-------------------------------------------------------------------------------------------------
/// 更新
void Player::update()
{
	move();
	shot();
}

//-------------------------------------------------------------------------------------------------
/// 描画
void Player::draw()
{
	mRenderer.render(mTransform);
}

//-------------------------------------------------------------------------------------------------
/// ボスの位置を設定する
/// @param aPos 
void Player::setBossPos(const Vector3& aPos)
{
	mBossPos = aPos;
}

//-------------------------------------------------------------------------------------------------
/// 移動
void Player::move()
{
	static const auto input = InputManager::getInst();
	mVelocity.x = input->getAxes().x;
	mVelocity.y = input->getAxes().y;

	static DirectX::XMVECTOR localPos = { 0, 0, -mDistanceFromBoss, 1 };

	// 緯度経度の差分移動
	DirectX::XMVECTOR velocity = { mVelocity.x, mVelocity.y, 0, 1 };
	DirectX::XMVECTOR dl = DirectX::XMVector3TransformCoord(velocity, mPoseMat);
	if (dl.m128_f32[0] != 0.0f || dl.m128_f32[1] != 0.0f || dl.m128_f32[2] != 0.0f) {
		// 移動
		DirectX::XMVECTOR zAxis = mPoseMat.r[2];
		DirectX::XMVECTOR rotAxis = DirectX::XMVector3Cross(dl, zAxis);

		DirectX::XMVECTOR transQ = DirectX::XMQuaternionRotationAxis(rotAxis, MOVE_SPEED);
		DirectX::XMMATRIX transRotMat = DirectX::XMMatrixRotationQuaternion(transQ);
		localPos = DirectX::XMVector3TransformCoord(localPos, transRotMat);
		mTransform.rot *= Quaternion(transQ);

		// 移動後姿勢更新
		DirectX::XMVECTOR x = {}, y = {}, z = {};
		z = localPos;
		z.m128_f32[0] *= -1;
		z.m128_f32[1] *= -1;
		z.m128_f32[2] *= -1;
		z = DirectX::XMVector3Normalize(z);

		y = mPoseMat.r[1];
		x = DirectX::XMVector3Cross(y, z);
		x = DirectX::XMVector3Normalize(x);

		y = DirectX::XMVector3Cross(z, x);
		y = DirectX::XMVector3Normalize(y);

		mPoseMat = DirectX::XMMatrixIdentity();
		mPoseMat.r[0] = x;
		mPoseMat.r[1] = y;
		mPoseMat.r[2] = z;
	}

	// ボスとの距離更新
	float offsetZ = 0;
	DirectX::XMVECTOR length = DirectX::XMVector3Length(localPos);
	DirectX::XMStoreFloat(&mDistanceFromBoss, length);
	if (mDistanceFromBoss - offsetZ > 0) {
		DirectX::XMVECTOR z = localPos;
		z = localPos;
		z.m128_f32[0] *= -1;
		z.m128_f32[1] *= -1;
		z.m128_f32[2] *= -1;
		z = DirectX::XMVector3Normalize(z);

		localPos.m128_f32[0] += offsetZ * z.m128_f32[0];
		localPos.m128_f32[1] += offsetZ * z.m128_f32[1];
		localPos.m128_f32[2] += offsetZ * z.m128_f32[2];
		mDistanceFromBoss -= offsetZ;
	}

	// 座標位置更新
	mTransform.pos.x = localPos.m128_f32[0];
	mTransform.pos.y = localPos.m128_f32[1];
	mTransform.pos.z = localPos.m128_f32[2];

	// ボスの位置を中心にする
	mTransform.pos += mBossPos;
}

//-------------------------------------------------------------------------------------------------
/// ショット
void Player::shot()
{

}

} // namespace
// EOF
