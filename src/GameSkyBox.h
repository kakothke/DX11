#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"
#include "OBJRenderer.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// �X�J�C�{�b�N�X
class GameSkyBox : public BaseGameObject
{
public:
	/// name �R���X�g���N�^
	//@{
	GameSkyBox();
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
	OBJRenderer mRenderer;
	//@}

};

} // namespace
// EOF
