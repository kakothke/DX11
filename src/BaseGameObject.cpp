#include "BaseGameObject.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
BaseGameObject::BaseGameObject()
	: mTransform()
	, mTag(GameObjectTag::Untagged)
	, mActiveSelf(true)
{
}

//-------------------------------------------------------------------------------------------------
/// @param aTransform トランスフォーム
BaseGameObject::BaseGameObject(Transform aTransform)
	: mTransform(aTransform)
	, mTag(GameObjectTag::Untagged)
	, mActiveSelf(true)
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
const bool& BaseGameObject::activeSelf() const
{
	return mActiveSelf;
}

//-------------------------------------------------------------------------------------------------
void BaseGameObject::setTag(GameObjectTag aTag)
{
	mTag = aTag;
}

//-------------------------------------------------------------------------------------------------
void BaseGameObject::setActive(bool aValue)
{
	mActiveSelf = aValue;
}

} // namespace
// EOF
