#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"

//-------------------------------------------------------------------------------------------------
#include "OBJRenderer.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

class Player : public BaseGameObject
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	Player();
	~Player();
	//@}

	/// @name 更新/描画
	//@{
	void update() override;
	void draw() override;
	//@}

	/// @name ミスイベント
	//@{
	void missEvent();
	//@}

private:
	/// @name 内部実装
	//@{
	void move();
	void instanceEffect();
	//@}

	/// @name プライベートメンバ変数
	//@{
	OBJRenderer mRenderer;
	float mMoveSpeed;
	float mInstanceBoosterTimer;
	//@}

};

} // namespace
// EOF