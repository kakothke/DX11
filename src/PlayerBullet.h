#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"
#include "SpriteRenderer.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// �v���C���[�̒e
class PlayerBullet : public BaseGameObject
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	PlayerBullet();
	~PlayerBullet();
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
	//@}

};

} // namespace
// EOF
