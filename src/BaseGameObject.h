#pragma once

//-------------------------------------------------------------------------------------------------
#include "Transform.h"
#include "Vector2.h"
#include "GameObjectTag.h"
#include "Fps.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// �S�ẴQ�[���I�u�W�F�N�g�̊��N���X
class BaseGameObject
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	BaseGameObject();
	BaseGameObject(Transform aTransform);
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
	const bool& isActive() const;
	void setTag(GameObjectTag aTag);
	void setIsActive(bool aValue);
	//@}

protected:
	/// @name �v���e�N�e�b�h�����o�ϐ�
	//@{
	Transform mTransform;
	//@}

private:
	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	GameObjectTag mTag;
	bool mIsActive;
	//@}

};

} // namespace
// EOF
