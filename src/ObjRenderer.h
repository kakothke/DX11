#pragma once

//-------------------------------------------------------------------------------------------------
#include "Transform.h"
#include "ObjLoader.h"
#include "ShaderLoader.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// .objファイル描画クラス
class OBJRenderer
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	OBJRenderer();
	~OBJRenderer();
	//@}

	bool render(const Transform& aTransform);
	void setObjAndShaderData(const char* aOBJFileName, const char* aShaderFileName);

private:
	OBJData* mOBJData;
	ShaderData* mShaderData;

};

} // namespace
// EOF
