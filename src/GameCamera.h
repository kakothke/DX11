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

private:
	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	float mKatamuki;
	//@}

};

} // namespace
// EOF
