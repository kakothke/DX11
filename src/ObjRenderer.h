#pragma once

//-------------------------------------------------------------------------------------------------
#include "Transform.h"
#include "ObjLoader.h"
#include "ShaderLoader.h"

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

	void render(const Transform& aTransform);
	void setObjAndShaderData(const ObjList& aObjList, const ShaderList& aShaderList);

private:
	ObjData* mObjData;
	ShaderData* mShaderData;

};

} // namespace
// EOF
