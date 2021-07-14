#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"

//-------------------------------------------------------------------------------------------------
#include "OBJRenderer.h"
#include "Player.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

class Obstract : public BaseGameObject
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	Obstract();
	~Obstract();
	//@}

	/// @name �X�V/�`��
	//@{
	void initialize() override;
	void update() override;
	void draw() override;
	//@}

	/// @name �A�N�Z�T
	//@{
	void setMoveSpeed(const float& aSpeed);
	//@}


private:
	/// @name ��������
	//@{
	void collisionPlayer();
	//@}

	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	OBJRenderer mRenderer;
	static Player* mPlayer;
	Color mColor;
	float mMoveSpeed;
	//@}

};

} // namespace
// EOF