#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"
#include "GameObjectTag.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// �J�������N���X
/// @brief �ÓI�ȃJ�����Ƃ��Ă��g�p�\
class Camera : public BaseGameObject
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	Camera();
	Camera(Transform aTransform);
	Camera(Vector3 aCameraParam);
	Camera(Transform aTransform, Vector3 aCameraParam);
	virtual ~Camera();
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
