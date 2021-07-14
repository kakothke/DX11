#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"

//-------------------------------------------------------------------------------------------------
#include "OBJRenderer.h"
#include "Player.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

class Obstract : public BaseGameObject
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	Obstract();
	~Obstract();
	//@}

	/// @name 更新/描画
	//@{
	void initialize() override;
	void update() override;
	void draw() override;
	//@}

	/// @name アクセサ
	//@{
	void setMoveSpeed(const float& aSpeed);
	//@}


private:
	/// @name 内部実装
	//@{
	void collisionPlayer();
	//@}

	/// @name プライベートメンバ変数
	//@{
	OBJRenderer mRenderer;
	static Player* mPlayer;
	Color mColor;
	float mMoveSpeed;
	//@}

};

} // namespace
// EOF