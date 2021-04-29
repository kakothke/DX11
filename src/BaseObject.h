#pragma once

//-------------------------------------------------------------------------------------------------
#include "Transform.h"
#include "Tag.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// 全てのゲームオブジェクトの基底クラス
class BaseObject
{
public:
	/// @name コンストラクタ
	//@{
	BaseObject();
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
	const Tag& tag() const;
	const bool& isActive() const;
	void setTag(Tag aTag);
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
	Tag mTag;
	bool mIsActive;
	//@}

};

} // namespace
// EOF
