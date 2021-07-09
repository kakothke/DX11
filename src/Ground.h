#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"

//-------------------------------------------------------------------------------------------------
#include "OBJRenderer.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

class Ground : public BaseGameObject
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	Ground(const Transform& aTransform, const float& aSpeed);
	~Ground();
	//@}

	/// @name �X�V/�`��
	//@{
	void update() override;
	void draw() override;
	//@}

	/// @name �A�N�Z�T
	//@{
	void setMoveSpeed(const float aSpeed);
	//@}


private:
	/// @name �R���|�[�l���g
	//@{
	OBJRenderer mRenderer;
	//@}

	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	float mMoveSpeed;
	//@}

};

} // namespace
// EOF