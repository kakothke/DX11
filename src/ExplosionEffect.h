#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"

//-------------------------------------------------------------------------------------------------
#include "SpriteRenderer.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// �����G�t�F�N�g
class ExplosionEffect : public BaseGameObject
{
public:
	/// @name �R���X�g���N�^
	//@{
	ExplosionEffect(Vector3 aInstancePos);
	~ExplosionEffect();
	//@}

	/// @name ������/�X�V/�`��
	//@{
	void update() override;
	void draw() override;
	//@}

private:
	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	SpriteRenderer mRenderer;
	Color mColor;
	//@}

};

} // namespace
// EOF
