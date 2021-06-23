#pragma once

//-------------------------------------------------------------------------------------------------
#include "Transform.h"
#include "Vector2.h"
#include "GameObjectTag.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// 全てのゲームオブジェクトの基底クラス
class BaseGameObject
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	BaseGameObject();
	BaseGameObject(Transform aTransform);
	virtual ~BaseGameObject();
	//@}

	/// @name 外部呼出し用の初期化/更新/描画
	//@{
	virtual void initialize();
	virtual void update();
	virtual void draw();
	//@}

	/// @name アクセサ
	//@{
	const Transform& transform() const;
	const GameObjectTag& tag() const;
	const bool& isActive() const;
	void setTag(GameObjectTag aTag);
	void setIsActive(bool aValue);
	//@}

	Transform mTransform;
protected:
	/// @name プロテクテッドメンバ変数
	//@{
	//@}

private:
	/// @name プライベートメンバ変数
	//@{
	GameObjectTag mTag;
	bool mIsActive;
	//@}

};

} // namespace
// EOF
