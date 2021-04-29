#pragma once

//-------------------------------------------------------------------------------------------------
#include "Transform.h"
#include "GameObjectTag.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// 全てのゲームオブジェクトの基底クラス
class BaseGameObject
{
public:
	/// @name コンストラクタ
	//@{
	BaseGameObject();
	//@}

	/// @name 外部呼出し用の初期化/更新/描画
	//@{
	virtual void initialize();
	virtual void update();
	virtual void draw() const;
	//@}

	/// @name アクセサ
	//@{
	const Transform& transform() const;
	const GameObjectTag& tag() const;
	const bool& isActive() const;
	void setTag(GameObjectTag aTag);
	void setIsActive(bool aValue);
	//@}

protected:
	/// @name プロテクテッドメンバ変数
	//@{
	Transform mTransform;
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
