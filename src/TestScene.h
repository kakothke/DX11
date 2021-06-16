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
	/// @name コンストラクタ/仮想デストラクタ
	//@{
	TestScene(IChangeScene* aImpl);
	virtual ~TestScene();
	//@}

	/// @name 更新/描画
	//@{
	void update() override;
	void draw() override;
	void draw2D() override;
	void drawBackground() override;
	//@}

private:
	/// @name プライベートメンバ変数
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
