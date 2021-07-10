#pragma once

//-------------------------------------------------------------------------------------------------
#include "Transform.h"
#include "Vector2.h"
#include "GameObjectTag.h"
#include "Fps.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// 全てのゲームオブジェクトの基底クラス
class BaseGameObject
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	BaseGameObject();
	virtual ~BaseGameObject();
	//@}

	/// @name 更新/描画
	//@{
	virtual void update();
	virtual void draw();
	//@}

	/// @name アクセサ
	//@{
	const Transform& transform() const;
	const Transform& cameraTransform() const;
	const GameObjectTag& tag() const;
	const bool& activeSelf() const;
	void setCameraTransform(const Transform& aTransform);
	void setTag(GameObjectTag aTag);
	void setActive(bool aValue);
	//@}

protected:
	/// @name プロテクテッドメンバ変数
	//@{
	Transform mTransform;
	Transform mCameraTransform;
	//@}

private:
	/// @name プライベートメンバ変数
	//@{
	GameObjectTag mTag;
	bool mActiveSelf;
	//@}

};

} // namespace
// EOF
