#include "BaseGameObject.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
BaseGameObject::BaseGameObject()
	: mTransform()
	, mTag(GameObjectTag::Untagged)
	, mIsActive(true)
{
}

//-------------------------------------------------------------------------------------------------
/// 初期化処理
void BaseGameObject::initialize()
{
}

//-------------------------------------------------------------------------------------------------
/// 更新
void BaseGameObject::update()
{
}


//-------------------------------------------------------------------------------------------------
/// 描画
void BaseGameObject::draw() const
{
}

//-------------------------------------------------------------------------------------------------
const Transform& BaseGameObject::transform() const
{
	return mTransform;
}

//-------------------------------------------------------------------------------------------------
const GameObjectTag& BaseGameObject::tag() const
{
	return mTag;
}

//-------------------------------------------------------------------------------------------------
const bool& BaseGameObject::isActive() const
{
	return mIsActive;
}

//-------------------------------------------------------------------------------------------------
void BaseGameObject::setTag(GameObjectTag aTag)
{
	mTag = aTag;
}

//-------------------------------------------------------------------------------------------------
void BaseGameObject::setIsActive(bool aValue)
{
	mIsActive = aValue;
}

} // namespace
// EOF
