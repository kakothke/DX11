#pragma once

//-------------------------------------------------------------------------------------------------
#include "AbstractScene.h"

//-------------------------------------------------------------------------------------------------
#include "Camera.h"
#include "GameSkyBox.h"
#include "DirectionalLight.h"
#include "SpriteRenderer.h"
#include "OBJRenderer.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// �f�o�b�O�V�[��
class DebugScene : public AbstractScene
{
public:
	/// @name �R���X�g���N�^/���z�f�X�g���N�^
	//@{
	DebugScene(IChangeScene* aImpl);
	virtual ~DebugScene();
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
	Camera mCamera;
	GameSkyBox mSkyBox;
	DirectionalLight mDirectionalLight;
	OBJRenderer mOBJTest;
	SpriteRenderer mSpriteTest;
	//@}

};

} // namespace
// EOF
