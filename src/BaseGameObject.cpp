#include "BaseGameObject.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
BaseGameObject::BaseGameObject()
	: mTransform()
	, mCameraTransform()
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
const Transform& BaseGameObject::cameraTransform() const
{
	return mCameraTransform;
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
void BaseGameObject::setCameraTransform(const Transform& aTransform)
{
	mCameraTransform = aTransform;
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
