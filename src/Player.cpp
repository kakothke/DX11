#include "Player.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"
#include "InputManager.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
const static float DEFINE_MOVE_SPEED = 15.0f;
const static float DEFINE_MOVE_ROT = 45.0f;
const static Vector3 DEFINE_POS = Vector3(0.0f, 0.0f, 10.0f);

//-------------------------------------------------------------------------------------------------
const static auto INPUT_MANAGER = InputManager::getInst();
const static auto FPS = Fps::getInst();

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
Player::Player()
{
	// トランスフォーム設定
	mTransform.pos = DEFINE_POS;

	// 描画設定
	mRenderer.setOBJ(ResourceFileName::OBJ.at(OBJList::Player));
	mRenderer.setShader(ResourceFileName::Shader.at(ShaderList::Standard));
}

//-------------------------------------------------------------------------------------------------
/// デストラクタ
Player::~Player()
{

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
/// 移動
void Player::move()
{
	Vector3 rot = INPUT_MANAGER->axes() * DEFINE_MOVE_ROT;
	Vector3 velocity = INPUT_MANAGER->axesRaw();
	velocity.y = 0;
	mTransform.rot = Quaternion::Euler(Vector3(0.0f, 0.0f, -rot.x));
	mTransform.pos += velocity * DEFINE_MOVE_SPEED * FPS->deltaTime();
}

//-------------------------------------------------------------------------------------------------
/// ショット
void Player::shot()
{

}

} // namespace
// EOF
