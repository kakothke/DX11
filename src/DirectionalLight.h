#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"
#include "GameObjectTag.h"
#include "Color.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// �f�B���N�V���i�����C�g���N���X
/// @brief �ÓI�ȃf�B���N�V���i�����C�g�Ƃ��Ă��g�p�\
class DirectionalLight : public BaseGameObject
{
public:
	/// @name �R���X�g���N�^
	//@{
	DirectionalLight();
	DirectionalLight(Vector3 aRot);
	DirectionalLight(Color aColor);
	DirectionalLight(Vector3 aRot, Color aColor);
	//@}

	/// @name �X�V/�`��
	//@{
	void update() override;
	void draw() override;
	//@}


protected:
	/// @name �v���e�N�e�b�h�����o�֐�
	//@{
	/// �R���X�^���g�o�b�t�@���X�V����
	void updateConstantBuffer();
	//@}

	/// @name �v���e�N�e�b�h�����o�ϐ�
	//@{
	/// �J���[
	Color mColor;
	//@}

};

} // namespace
// EOF
