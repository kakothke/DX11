#pragma once

//-------------------------------------------------------------------------------------------------
namespace KDXK {

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
	bool initialize();
	/// メッセージループ
	void msgLoop();
	//@}

};

} // namespace
// EOF
