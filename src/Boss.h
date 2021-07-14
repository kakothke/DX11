#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"

//-------------------------------------------------------------------------------------------------
#include "OBJRenderer.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// ボス
class Boss : public BaseGameObject
{
public:
	/// name コンストラクタ
	//@{
	Boss();
	//@}

	/// @name 初期化/更新/描画
	//@{
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
