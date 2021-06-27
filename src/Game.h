#pragma once

//-------------------------------------------------------------------------------------------------
#include "SceneManager.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// ゲーム全体
class Game
{
public:
	/// @name コンストラクタ
	//@{
	Game();
	//@}

	/// @name 初期化処理
	//{
	bool initialize();
	//@}

	/// @name ゲームのメインループ
	//@{
	bool mainLoop();
	//@}

private:
	/// @name プライベートメンバ変数
	//@{
	/// シーン管理
	SceneManager mSceneManager;
	//@}

};

} // namespace
// EOF
