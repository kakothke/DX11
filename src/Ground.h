#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"

//-------------------------------------------------------------------------------------------------
#include "OBJRenderer.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

class Ground : public BaseGameObject
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	Ground(const Transform& aTransform, const float& aSpeed);
	~Ground();
	//@}

	/// @name 更新/描画
	//@{
	void update() override;
	void draw() override;
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
	float mMoveSpeed;
	//@}

};

} // namespace
// EOF