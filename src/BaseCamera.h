#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"

//-------------------------------------------------------------------------------------------------
#include "GameObjectTag.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// �J�������N���X
/// @brief �ÓI�ȃJ�����Ƃ��Ă��g�p�\
class BaseCamera : public BaseGameObject
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	BaseCamera();
	BaseCamera(Transform aTransform);
	BaseCamera(Vector3 aCameraParam);
	BaseCamera(Transform aTransform, Vector3 aCameraParam);
	virtual ~BaseCamera();
	//@}

	/// @name �X�V/�`��
	//@{
	void update() override;
	void draw() override;
	//@}

	/// @name �R���X�^���g�o�b�t�@���X�V����
	//@{
	void updateConstantBuffer();
	//@}

protected:
	/// @name �v���e�N�e�b�h�����o�ϐ�
	//@{
	float mFov;
	float mNearZ;
	float mFarZ;
	//@}

};

} // namespace
// EOF
