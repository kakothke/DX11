#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"
#include "OBJRenderer.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// 立方体
class TestSky : public BaseGameObject
{
public:
	/// name コンストラクタ
	//@{
	TestSky();
	TestSky(Transform aTransform);
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
