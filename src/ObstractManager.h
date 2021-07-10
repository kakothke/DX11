#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"

//-------------------------------------------------------------------------------------------------
#include <memory>

//-------------------------------------------------------------------------------------------------
#include "Ground.h"
#include "Obstract.h"
#include "Vector3.h"

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

	/// @name オブジェクト
	//@{
	/// 地上
	std::list<std::shared_ptr<Ground>> mGround;
	/// 障害物
	std::list<std::shared_ptr<Obstract>> mObstract;
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
