#include "BaseGameObject.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
BaseGameObject::BaseGameObject()
	: mTransform()
	, mTag(GameObjectTag::Untagged)
	, mIsActive(true)
{
}

//-------------------------------------------------------------------------------------------------
/// @param aTransform �g�����X�t�H�[��
BaseGameObject::BaseGameObject(Transform aTransform)
	: mTransform(aTransform)
	, mTag(GameObjectTag::Untagged)
	, mIsActive(true)
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
