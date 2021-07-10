#pragma once

//-------------------------------------------------------------------------------------------------
#include "AbstractScene.h"

//-------------------------------------------------------------------------------------------------
#include "GameCamera.h"
#include "GameSkyBox.h"
#include "DirectionalLight.h"
#include "Player.h"
#include "ObstractManager.h"
#include "GameObjectManager.h"

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
	/// @name �񋓌^
	//@{
	/// �Q�[����
	enum class GameState
	{
		Intro,
		Game,
		Miss,
	};
	//@}

	/// @name �V�[�����Q�[���I�u�W�F�N�g
	//@{
	GameCamera* mCamera;
	Player* mPlayer;
	//@}

	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	GameObjectManager mGameOBJManager;
	GameState mState;
	//@}

};

} // namespace
// EOF
