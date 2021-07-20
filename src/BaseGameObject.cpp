#include "BaseGameObject.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
Fps* BaseGameObject::mFps = Fps::getInst();

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
/// @param aTransform �����g�����X�t�H�[��
BaseGameObject::BaseGameObject(Transform aTransform)
	: mTransform(aTransform)
	, mGameObjectList(nullptr)
	, mTag(GameObjectTag::Untagged)
	, mActiveSelf(true)
	, mDestroyFlag(false)
{
}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
BaseGameObject::~BaseGameObject()
{
}

//-------------------------------------------------------------------------------------------------
/// ������
void BaseGameObject::initialize()
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
const bool& BaseGameObject::activeSelf() const
{
	return mActiveSelf;
}

//-------------------------------------------------------------------------------------------------
const bool& BaseGameObject::destroyFlag() const
{
	return mDestroyFlag;
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

//-------------------------------------------------------------------------------------------------
void BaseGameObject::setGameObjectList(ISetGameObject* aImpl)
{
	mGameObjectList = aImpl;
}

//-------------------------------------------------------------------------------------------------
void BaseGameObject::destroyThisGameObject()
{
	mDestroyFlag = true;
}

} // namespace
// EOF
