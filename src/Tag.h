#pragma once

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// ゲームオブジェクトを見分ける為の構造体
enum class Tag
{
	Untagged,

	Camera,
	Light,
	Cube,

	TERM
};

} // namespace
// EOF
