#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"

//-------------------------------------------------------------------------------------------------
#include "OBJRenderer.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

class Player : public BaseGameObject
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	Player();
	~Player();
	//@}

	/// @name �X�V/�`��
	//@{
	void update() override;
	void draw() override;
	//@}

private:
	/// @name ��������
	//@{
	void move();
	void shot();
	void instanceEffect();
	//@}

	/// @name �R���|�[�l���g
	//@{
	OBJRenderer mRenderer;
	//@}

	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	float mMoveSpeed;
	float mInstanceBoosterTimer;
	//@}

};

} // namespace
// EOF