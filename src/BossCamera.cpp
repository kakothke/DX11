#include "BossCamera.h"

//-------------------------------------------------------------------------------------------------
#include "TestPlayer.h"
#include "Direct3D11.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
BossCamera::BossCamera()
	: mDistanceFromPlayer(20.0f)
{
}

//-------------------------------------------------------------------------------------------------
/// 更新
void BossCamera::update()
{
	const static auto PLAYER_OBJ = (TestPlayer*)mGameObjectList->findGameObject(GameObjectTag::Player);

	// プレイヤーを親オブジェクトとして連動させる
	mTransform = PLAYER_OBJ->transform();
	mTransform.localPos = -PLAYER_OBJ->moveVelocity();
	mTransform.localPos.z = -mDistanceFromPlayer;
}

//-------------------------------------------------------------------------------------------------
/// 描画
void BossCamera::draw()
{
}

} // namespace
// EOF
