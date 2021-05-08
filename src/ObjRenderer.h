#pragma once

//-------------------------------------------------------------------------------------------------
#include <D3D11.h>
#include "Transform.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// .objファイル描画クラス
class ObjRenderer
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	ObjRenderer();
	~ObjRenderer();
	//@}

	void initialize();
	void render(Transform aTransform);

private:
	

};

} // namespace
// EOF
