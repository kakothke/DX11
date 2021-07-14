#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseCamera.h"

//-------------------------------------------------------------------------------------------------
#include "Player.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// �Q�[���J����
class GameCamera : public BaseCamera
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	GameCamera();
	~GameCamera();
	//@}

	/// @name ������/�X�V/�`��
	//@{
	void initialize() override;
	void update() override;
	void draw() override;
	//@}

private:
	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	Player* mPlayer;
	float mKatamuki;
	//@}

};

} // namespace
// EOF
