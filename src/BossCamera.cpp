#include "BossCamera.h"

//-------------------------------------------------------------------------------------------------
#include "TestPlayer.h"
#include "Direct3D11.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
BossCamera::BossCamera()
	: mPlayer(nullptr)
	, mDistanceFromPlayer(20.0f)
{
}

//-------------------------------------------------------------------------------------------------
/// 初期化
void BossCamera::initialize()
{
	mPlayer = (TestPlayer*)mGameObjectList->findWorldGameObject(GameObjectTag::Player);
}

//-------------------------------------------------------------------------------------------------
/// 更新
void BossCamera::update()
{
	// プレイヤーを親オブジェクトとして連動させる
	mTransform = mPlayer->transform();
	mTransform.localPos = -mPlayer->moveVelocity();
	mTransform.localPos.z = -mDistanceFromPlayer;
}

//-------------------------------------------------------------------------------------------------
/// 描画
void BossCamera::draw()
{
}

} // namespace
// EOF
