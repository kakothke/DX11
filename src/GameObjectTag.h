#pragma once

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// ゲームオブジェクトを見分ける為の構造体
enum class GameObjectTag
{
	Untagged,

	Camera,
	Player,
	Boss,
	Ground,
	Obstract,

	Effect_MoveLine,

};

} // namespace
// EOF
