#pragma once

//-------------------------------------------------------------------------------------------------
#include "Camera.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// �Q�[���J����
class GameCamera : public Camera
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	GameCamera();
	~GameCamera();
	//@}

	/// @name �X�V/�`��
	//@{
	void update() override;
	void draw() override;
	//@}

	/// @name �A�N�Z�T
	//@{
	void setPlayerPos(const Vector3& aPos);
	//@}

private:
	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	Vector3 mPlayerPos;
	//@}

};

} // namespace
// EOF
