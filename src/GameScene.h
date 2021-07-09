#pragma once

//-------------------------------------------------------------------------------------------------
#include "AbstractScene.h"

//-------------------------------------------------------------------------------------------------
#include "GameCamera.h"
#include "GameSkyBox.h"
#include "DirectionalLight.h"
#include "Player.h"
#include "ObstractManager.h"

//-------------------------------------------------------------------------------------------------
#include "SpriteRenderer.h"
#include "OBJRenderer.h"

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
	void draw2D() override;
	void drawBackground() override;
	//@}

private:
	/// @name �V�[�����Q�[���I�u�W�F�N�g
	//@{
	GameCamera mCamera;
	GameSkyBox mSkyBox;
	DirectionalLight mDirectionalLight;
	Player mPlayer;
	ObstractManager mObstractManager;

	OBJRenderer mOBJTest;
	SpriteRenderer mSpriteTest;
	//@}

};

} // namespace
// EOF
