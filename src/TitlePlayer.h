#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"

//-------------------------------------------------------------------------------------------------
#include "OBJRenderer.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

class TitlePlayer : public BaseGameObject
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	TitlePlayer();
	~TitlePlayer();
	//@}

	/// @name 更新/描画
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