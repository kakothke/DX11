#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseCamera.h"

//-------------------------------------------------------------------------------------------------
#include "OBJRenderer.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// タイトルカメラ
class TitleCamera : public BaseCamera
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	TitleCamera();
	~TitleCamera();
	//@}

	/// @name 更新/描画
	//@{
	void update() override;
	void draw() override;
	//@}

private:

};

} // namespace
// EOF
