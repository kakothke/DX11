#include "BaseGameObject.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
Fps* BaseGameObject::mFps = Fps::getInst();

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
/// @param aTransform 初期トランスフォーム
BaseGameObject::BaseGameObject(Transform aTransform)
	: mTransform(aTransform)
	, mGameObjectList(nullptr)
	, mTag(GameObjectTag::Untagged)
	, mActiveSelf(true)
	, mDestroyFlag(false)
{
}

//-------------------------------------------------------------------------------------------------
/// デストラクタ
BaseGameObject::~BaseGameObject()
{
}

//-------------------------------------------------------------------------------------------------
/// 初期化
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
