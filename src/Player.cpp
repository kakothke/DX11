#include "Player.h"

//-------------------------------------------------------------------------------------------------
#include "MyOutputDebugString.h" 
#include "ResourceFileName.h"
#include "InputManager.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// 定数
const static float DEFINE_TARGET_DISTANCE = 100.0f;
const static float DEFINE_MOVE_VELOCITY = 1.0f;

//-------------------------------------------------------------------------------------------------
/// シングルトンクラス
const static auto INPUT_MANAGER = InputManager::getInst();
const static auto FPS = Fps::getInst();

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
Player::Player()
	: mRenderer()
	, mTargetPos()
	, mTargetDistance(DEFINE_TARGET_DISTANCE)
	, mMoveVelocity(DEFINE_MOVE_VELOCITY)
{
	// 描画設定
	mRenderer.setOBJ(ResourceFileName::OBJ.at(OBJList::Player));
	mRenderer.setShader(ResourceFileName::Shader.at(ShaderList::Standard));
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
	mTargetPos = aPos;
}

//-------------------------------------------------------------------------------------------------
/// 移動
void Player::move()
{
	// 入力
	Vector2 axis = INPUT_MANAGER->getAxes();

	// 速度
	Vector2 angle = mMoveVelocity * FPS->deltaTime();
	if (axis.SqrMagnitude() == 2) {
		// 斜め移動は√2で割る
		angle /= sqrt(2);
	}

	// 移動
	mTransform.rot *= Quaternion::AxisAngle(mTransform.Up() * -axis.x, angle.x);
	mTransform.rot *= Quaternion::AxisAngle(mTransform.Right() * axis.y, angle.y);
	mTransform.pos = mTargetPos + mTransform.rot * Vector3::back * mTargetDistance;
}

//-------------------------------------------------------------------------------------------------
/// ショット
void Player::shot()
{

}

} // namespace
// EOF
