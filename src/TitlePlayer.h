#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"

//-------------------------------------------------------------------------------------------------
#include "OBJRenderer.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

class TitlePlayer : public BaseGameObject
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	TitlePlayer();
	~TitlePlayer();
	//@}

	/// @name �X�V/�`��
	//@{
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