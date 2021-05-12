#pragma once

//-------------------------------------------------------------------------------------------------
#include "IChangeScene.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// �V�[���̊�{�N���X
class AbstractScene
{
public:
	/// @name �R���X�g���N�^/���z�f�X�g���N�^
	//@{
	AbstractScene(IChangeScene* aImpl) : mImplSceneChanged(aImpl) {}
	virtual ~AbstractScene() = default;
	//@}

	// @name ���z�֐�
	//@{
	virtual void update() = 0;
	virtual void draw() = 0;
	//@}

protected:
	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	/// �V�[���J�ڃC���^�[�t�F�[�X
	IChangeScene* mImplSceneChanged;
	//@}

};

} // namespace
// EOF
