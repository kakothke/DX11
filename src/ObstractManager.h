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
	/// レベル更新
	void updateLevel();
	/// オブジェクトを生成する
	void instanceObj();
	/// 障害物を生成する
	void instanceObstract();
	/// 地上を生成する
	void instanceGround();
	/// スピード変更
	void changeSpeed();
	//@}

	/// @name プライベートメンバ変数
	//@{
	/// レベルアップタイマー
	float mLevelUpTimer;
	/// 障害物生成タイマー
	float mInstanceObstractTimer;
	/// 地上生成タイマー
	float mInstanceGroundTimer;
	/// スピード
	float mMoveSpeed;
	/// レベル
	int mLevel;
	/// 障害物生成数
	int mInstanceObstractCount;
	//@}

};

} // namespace
// EOF
