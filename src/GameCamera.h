#pragma once

//-------------------------------------------------------------------------------------------------
#include "Camera.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// �J�������N���X
/// @brief �ÓI�ȃJ�����Ƃ��Ă��g�p�\
class GameCamera : public Camera
{
public:
	/// @name �R���X�g���N�^
	//@{
	GameCamera();
	GameCamera(Transform aTransform);
	GameCamera(Vector3 aCameraParam);
	GameCamera(Transform aTransform, Vector3 aCameraParam);
	//@}

	/// @name �X�V/�`��
	//@{
	void update() override;
	void draw() override;
	//@}

private:

};

} // namespace
// EOF
