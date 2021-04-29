#pragma once

//-------------------------------------------------------------------------------------------------
#include "Transform.h"
#include "Tag.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// �S�ẴQ�[���I�u�W�F�N�g�̊��N���X
class BaseObject
{
public:
	/// @name �R���X�g���N�^
	//@{
	BaseObject();
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
	const Tag& tag() const;
	const bool& isActive() const;
	void setTag(Tag aTag);
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
	Tag mTag;
	bool mIsActive;
	//@}

};

} // namespace
// EOF
