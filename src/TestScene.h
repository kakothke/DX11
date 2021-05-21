#pragma once

//-------------------------------------------------------------------------------------------------
#include "AbstractScene.h"
#include "Cube.h"
#include "Sphere.h"
#include "Camera.h"
#include "TestObj.h"
#include "DirectionalLight.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

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
	//@}

private:
	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	//Cube mCube;
	//Sphere mSphere;
	TestObj mTestObj;
	Camera mCamera;
	DirectionalLight mDirectionalLight;
	
	//@}

};

} // namespace
// EOF
