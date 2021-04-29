#pragma once

//-------------------------------------------------------------------------------------------------
#include <Windows.h>
#include "Game.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// システム管理クラス
class SystemMain
{
public:
	/// @name コンストラクタ
	//@{
	SystemMain();
	//@}

	/// @name WinMainから呼び出される関数
	//@{
	/// 初期化処理
	bool initialize() const;
	/// メッセージループ
	void msgLoop();
	//@}

private:
	/// @name プライベートメンバ変数
	//@{
	//@}

};

} // namespace
// EOF
