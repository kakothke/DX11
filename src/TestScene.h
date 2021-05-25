#pragma once

//-------------------------------------------------------------------------------------------------
#include "AbstractScene.h"
#include "Camera.h"
#include "TestObj.h"
#include "DirectionalLight.h"

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
	TestObj mTestObj;
	Camera mCamera;
	DirectionalLight mDirectionalLight;
	
	//@}

};

} // namespace
// EOF
