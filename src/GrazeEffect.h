#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"

//-------------------------------------------------------------------------------------------------
#include "SpriteRenderer.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

class GrazeEffect : public BaseGameObject
{
public:
	/// @name �R���X�g���N�^
	//@{
	GrazeEffect(Vector3 aObstractPos, Vector3 aPlayerPos);
	~GrazeEffect();
	//@}

	/// @name �X�V/�`��
	//@{
	void update() override;
	void draw() override;
	//@}

private:
	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	SpriteRenderer mRenderer;
	Vector3 mVelocity;
	//@}

};

} // namespace
// EOF
