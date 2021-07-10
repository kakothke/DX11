#pragma once

//-------------------------------------------------------------------------------------------------
#include "ISetGameObjectList.h"
#include "Transform.h"
#include "Vector2.h"
#include "GameObjectTag.h"
#include "Fps.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// �O���錾
class ISetGameObject;

/// �S�ẴQ�[���I�u�W�F�N�g�̊��N���X
class BaseGameObject
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	BaseGameObject(Transform aTransform = Transform());
	virtual ~BaseGameObject();
	//@}

	/// @name �X�V/�`��
	//@{
	virtual void update();
	virtual void draw();
	//@}

	/// @name �A�N�Z�T
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
	/// @name �v���e�N�e�b�h�����o�ϐ�
	//@{
	Transform mTransform;
	ISetGameObject* mGameObjectList;
	//@}

private:
	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	GameObjectTag mTag;
	bool mActiveSelf;
	bool mDestroyFlag;
	//@}

};

} // namespace
// EOF
