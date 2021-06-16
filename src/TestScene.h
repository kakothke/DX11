#pragma once

//-------------------------------------------------------------------------------------------------
#include "AbstractScene.h"
#include "Camera.h"
#include "TestObj.h"
#include "TestSprite.h"
#include "TestSky.h"
#include "Cube.h"
#include "DirectionalLight.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

class TestScene : public AbstractScene
{
public:
	/// @name �R���X�g���N�^/���z�f�X�g���N�^
	//@{
	TestScene(IChangeScene* aImpl);
	virtual ~TestScene();
	//@}

	/// @name �X�V/�`��
	//@{
	void update() override;
	void draw() override;
	void draw2D() override;
	void drawBackground() override;
	//@}

private:
	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	TestObj mTestObj;
	TestSprite mTestSprite, mT2;
	TestSky mTestSky;
	Camera mCamera;
	DirectionalLight mDirectionalLight;
	
	//@}

};

} // namespace
// EOF
