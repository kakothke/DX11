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
	/// @name 内部実装
	//@{
	void instanceEffect();
	//@}

	/// @name プライベートメンバ変数
	//@{
	OBJRenderer mRenderer;
	float mInstanceBoosterTimer;
	//@}

};

} // namespace
// EOF