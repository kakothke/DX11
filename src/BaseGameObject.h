#pragma once

//-------------------------------------------------------------------------------------------------
#include "ISetGameObjectList.h"
#include "Transform.h"
#include "Vector2.h"
#include "GameObjectTag.h"
#include "Fps.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// 前方宣言
class ISetGameObject;

/// 全てのゲームオブジェクトの基底クラス
class BaseGameObject
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	BaseGameObject(Transform aTransform = Transform());
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
	const GameObjectTag& tag() const;
	const bool& activeSelf() const;
	const bool& destroyFlag() const;
	void setTag(GameObjectTag aTag);
	void setActive(bool aValue);
	void setGameObjectList(ISetGameObject* aImpl);
	void destroyThisGameObject();
	//@}

protected:
	/// @name プロテクテッドメンバ変数
	//@{
	Transform mTransform;
	ISetGameObject* mGameObjectList;
	//@}

private:
	/// @name プライベートメンバ変数
	//@{
	GameObjectTag mTag;
	bool mActiveSelf;
	bool mDestroyFlag;
	//@}

};

} // namespace
// EOF
