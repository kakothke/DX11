#pragma once

//-------------------------------------------------------------------------------------------------
#include "IChangeScene.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// シーンの基本クラス
class AbstractScene
{
public:
	/// @name コンストラクタ/仮想デストラクタ
	//@{
	AbstractScene(IChangeScene* aImpl) : mImplSceneChanged(aImpl) {}
	virtual ~AbstractScene() = default;
	//@}

	// @name 仮想関数
	//@{
	virtual void update() = 0;
	virtual void draw() = 0;
	//@}

protected:
	/// @name プライベートメンバ変数
	//@{
	/// シーン遷移インターフェース
	IChangeScene* mImplSceneChanged;
	//@}

};

} // namespace
// EOF
