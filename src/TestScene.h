#pragma once

//-------------------------------------------------------------------------------------------------
#include "AbstractScene.h"
#include "Cube.h"

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
	void draw() const override;
	//@}

private:
	/// @name プライベートメンバ変数
	//@{
	Cube mCube;
	//@}

};

} // namespace
// EOF
