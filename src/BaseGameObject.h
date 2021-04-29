#pragma once

//-------------------------------------------------------------------------------------------------
#include "Transform.h"
#include "GameObjectTag.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// �S�ẴQ�[���I�u�W�F�N�g�̊��N���X
class BaseGameObject
{
public:
	/// @name �R���X�g���N�^
	//@{
	BaseGameObject();
	//@}

	/// @name �O���ďo���p�̏�����/�X�V/�`��
	//@{
	virtual void initialize();
	virtual void update();
	virtual void draw() const;
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
