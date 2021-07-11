#pragma once

//-------------------------------------------------------------------------------------------------
#include "Camera.h"

//-------------------------------------------------------------------------------------------------
#include "OBJRenderer.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// タイトルカメラ
class TitleCamera : public Camera
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
