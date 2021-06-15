#pragma once

//-------------------------------------------------------------------------------------------------
#include <DirectXMath.h>
#include "Resource.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// .objファイル描画クラス
class OBJRenderer
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	OBJRenderer();
	~OBJRenderer();
	//@}

	bool render(const DirectX::XMFLOAT3X3& aTransform);
	void setObjAndShaderData(const char* aOBJFileName, const char* aShaderFileName);

private:
	OBJData* mOBJData;
	ShaderData* mShaderData;

};

} // namespace
// EOF
