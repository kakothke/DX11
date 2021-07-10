#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

class ObstractManager : public BaseGameObject
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	ObstractManager();
	~ObstractManager();
	//@}
	
	/// @name 更新/描画
	//@{
	void update() override;
	void draw() override;
	//@}

	/// @name 当たり判定
	//@{
	bool collisionPlayer(const Vector3& aPos);
	//@}

private:
	/// @name 内部実装
	//@{
	/// オブジェクトを生成する
	void instanceObj();
	/// 地上を生成する
	void instanceGround();
	/// 障害物を生成する
	void instanceObstract();
	/// スピード変更
	void changeSpeed();
	//@}

	/// @name プライベートメンバ変数
	//@{
	/// スピード
	float mSpeed;
	/// レベル
	int mLevel;
	//@}

};

} // namespace
// EOF
