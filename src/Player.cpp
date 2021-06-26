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
	static auto input = InputManager::getInst();
	Vector3 axis;
	axis.x = input->getAxes().y;
	axis.y = -input->getAxes().x;
	Quaternion rotQ = Quaternion::AxisAngle(axis, 0.01f);
	mTransform.pos -= mBossPos;
	mTransform.pos *= rotQ;
	mTransform.rot *= rotQ;
	mTransform.pos += mBossPos;
}

//-------------------------------------------------------------------------------------------------
/// ショット
void Player::shot()
{

}

} // namespace
// EOF
