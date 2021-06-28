#include "BaseGameObject.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
BaseGameObject::BaseGameObject()
	: mTransform()
	, mTag(GameObjectTag::Untagged)
	, mIsActive(true)
{
}

//-------------------------------------------------------------------------------------------------
/// @param aTransform トランスフォーム
BaseGameObject::BaseGameObject(Transform aTransform)
	: mTransform(aTransform)
	, mTag(GameObjectTag::Untagged)
	, mIsActive(true)
{
}

//-------------------------------------------------------------------------------------------------
/// デストラクタ
BaseGameObject::~BaseGameObject()
{
}

//-------------------------------------------------------------------------------------------------
/// 更新
void BaseGameObject::update()
{
}


//-------------------------------------------------------------------------------------------------
/// 描画
void BaseGameObject::draw()
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
