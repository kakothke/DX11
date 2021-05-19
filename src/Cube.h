#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"
#include "OBJRenderer.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// 立方体
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
	OBJRenderer mRenderer;
	//@}

};

} // namespace
// EOF
