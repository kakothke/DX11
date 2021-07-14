#pragma once

//-------------------------------------------------------------------------------------------------
#include "AbstractScene.h"

//-------------------------------------------------------------------------------------------------
#include "GameObjectManager.h"
#include "Player.h"
#include "StageManager.h"
#include "GameUI.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// �Q�[���V�[��
class GameScene : public AbstractScene
{
public:
	/// @name �R���X�g���N�^/���z�f�X�g���N�^
	//@{
	GameScene(IChangeScene* aImpl);
	virtual ~GameScene();
	//@}

	/// @name �X�V/�`��
	//@{
	void update() override;
	void draw() override;
	//@}

private:
	/// @name ��������
	//@{
	void missEvent();
	//@}

	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	GameObjectManager mGameOBJManager;
	Player* mPlayer;
	StageManager* mStageManager;
	GameUI* mGameUI;
	float mRetryWaitTimer;
	bool mMissFlag;
	bool mRetryFlag;
	//@}

};

} // namespace
// EOF
