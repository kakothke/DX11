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

private:
	/// @name 内部実装
	//@{
	void move();
	void shot();
	//@}

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