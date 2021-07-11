#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"

//-------------------------------------------------------------------------------------------------
#include "OBJRenderer.h"

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
	void update() override;
	void draw() override;
	//@}

	/// @name 当たり判定
	//@{
	Transform getCollision();
	//@}

	/// @name アクセサ
	//@{
	void setMoveSpeed(const float aSpeed);
	//@}


private:
	/// @name コンポーネント
	//@{
	OBJRenderer mRenderer;
	//@}

	/// @name プライベートメンバ変数
	//@{
	Color mColor;
	float mMoveSpeed;
	//@}

};

} // namespace
// EOF