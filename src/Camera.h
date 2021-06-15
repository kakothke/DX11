#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"
#include "GameObjectTag.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// �S�ẴQ�[���I�u�W�F�N�g�̊��N���X
class Camera : public BaseGameObject
{
public:
	/// @name �R���X�g���N�^
	//@{
	Camera();
	//@}

	/// @name �X�V/�`��
	//@{
	void update() override;
	void draw() override;
	//@}


protected:
	/// @name �v���e�N�e�b�h�����o�֐�
	//@{
	void updateConstantBuffer();
	//@}

	/// @name �v���e�N�e�b�h�����o�ϐ�
	//@{
	float mFov;
	float mNearZ;
	float mFarZ;
	//@}

};

} // namespace
// EOF
