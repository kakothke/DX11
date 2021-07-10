#include "BaseGameObject.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
BaseGameObject::BaseGameObject()
	: mTransform()
	, mCameraTransform()
	, mTag(GameObjectTag::Untagged)
	, mActiveSelf(true)
{
}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
BaseGameObject::~BaseGameObject()
{
}

//-------------------------------------------------------------------------------------------------
/// �X�V
void BaseGameObject::update()
{
}


//-------------------------------------------------------------------------------------------------
/// �`��
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
