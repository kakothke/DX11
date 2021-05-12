#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"
#include "ObjRenderer.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// テスト用のゲームオブジェクト
class Cube : public BaseGameObject
{
public:
	/// name コンストラクタ
	//@{
	Cube();
	Cube(Transform aTransform);
	//@}

	/// @name 初期化/更新/描画
	//@{
	void initialize() override;
	void update() override;
	void draw() override;
	//@}

private:
	/// @name プライベートメンバ変数
	//@{
	ObjRenderer mRenderer;
	//@}

};

} // namespace
// EOF
