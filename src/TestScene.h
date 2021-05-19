#pragma once

//-------------------------------------------------------------------------------------------------
#include "AbstractScene.h"
#include "Cube.h"
#include "Sphere.h"
#include "Camera.h"
#include "TestObj.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

class TestScene : public AbstractScene
{
public:
	/// @name コンストラクタ/仮想デストラクタ
	//@{
	TestScene(IChangeScene* aImpl);
	virtual ~TestScene();
	//@}

	/// @name 更新/描画
	//@{
	void update() override;
	void draw() override;
	//@}

private:
	/// @name プライベートメンバ変数
	//@{
	Cube mCube;
	Sphere mSphere;
	TestObj mTestObj;
	Camera mCamera;
	//@}

};

} // namespace
// EOF
