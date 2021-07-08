#pragma once

//-------------------------------------------------------------------------------------------------
#include "AbstractScene.h"

//-------------------------------------------------------------------------------------------------
#include "GameCamera.h"
#include "GameSkyBox.h"
#include "DirectionalLight.h"
#include "Player.h"
#include "Boss.h"
#include "FontRenderer.h"
#include "SpriteRenderer.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// �{�X��e�X�g�V�[��
class BossTestScene : public AbstractScene
{
public:
	/// @name �R���X�g���N�^/���z�f�X�g���N�^
	//@{
	BossTestScene(IChangeScene* aImpl);
	virtual ~BossTestScene();
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
	Boss mBoss;
	FontRenderer mFontTest;
	SpriteRenderer mSpriteTest;
	//@}

};

} // namespace
// EOF
