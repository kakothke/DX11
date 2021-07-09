#include "GameCamera.h"

//-------------------------------------------------------------------------------------------------
#include "InputManager.h"
#include "Math.h"
#include "MyOutputDebugString.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
const static auto FPS = Fps::getInst();
const static auto INPUT_MANAGER = InputManager::getInst();

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
GameCamera::GameCamera()
	: mPlayerPos()
{
}

//-------------------------------------------------------------------------------------------------
/// 更新
void GameCamera::update()
{
	static float decelerate = 1.0f;
	float speed = 10.0f * FPS->deltaTime();
	if (INPUT_MANAGER->getButton(InputCode::Cancel)) {
		if (decelerate != 1.0f / 4.0f) {
			decelerate = Math::Lerp(decelerate, 1.0f / 4.0f, speed);
		}
	} else {
		if (decelerate < 1.0f) {
			decelerate = Math::Lerp(decelerate, 1.0f, speed);
		}
	}

	float x = INPUT_MANAGER->axes().x * decelerate;

	// プレイヤーを親オブジェクトとして連動させる
	mTransform.pos = mPlayerPos;
	mTransform.localPos.x = x * -2.0f;
	mTransform.localPos.y = 0.5f;
	mTransform.localPos.z = -20.0f;
	mTransform.localRot = Quaternion::Euler(Vector3(0.0f, x, x * 6.0f));

	// コンスタントバッファ更新
	updateConstantBuffer();
}

//-------------------------------------------------------------------------------------------------
/// 描画
void GameCamera::draw()
{
}

//-------------------------------------------------------------------------------------------------
void GameCamera::setPlayerPos(const Vector3& aPos)
{
	mPlayerPos = aPos;
}

} // namespace
// EOF
