
#pragma once

//-------------------------------------------------------------------------------------------------
#include "AbstractScene.h"

//-------------------------------------------------------------------------------------------------
#include "GameObjectManager.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// �Q�[���V�[��
class TitleScene : public AbstractScene
{
public:
	/// @name �R���X�g���N�^/���z�f�X�g���N�^
	//@{
	TitleScene(IChangeScene* aImpl);
	virtual ~TitleScene();
	//@}

	/// @name �X�V/�`��
	//@{
	void update() override;
	void draw() override;
	//@}

private:
	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	GameObjectManager mGameOBJManager;
	float mSceneChangeWaitTimer;
	bool mStartFlag;
	//@}

};

} // namespace
// EOF
