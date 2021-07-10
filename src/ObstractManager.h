#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

class ObstractManager : public BaseGameObject
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	ObstractManager();
	~ObstractManager();
	//@}
	
	/// @name �X�V/�`��
	//@{
	void update() override;
	void draw() override;
	//@}

	/// @name �����蔻��
	//@{
	bool collisionPlayer(const Vector3& aPos);
	//@}

private:
	/// @name ��������
	//@{
	/// �I�u�W�F�N�g�𐶐�����
	void instanceObj();
	/// �n��𐶐�����
	void instanceGround();
	/// ��Q���𐶐�����
	void instanceObstract();
	/// �X�s�[�h�ύX
	void changeSpeed();
	//@}

	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	/// �X�s�[�h
	float mSpeed;
	/// ���x��
	int mLevel;
	//@}

};

} // namespace
// EOF
