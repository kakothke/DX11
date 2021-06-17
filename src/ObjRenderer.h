#pragma once

//-------------------------------------------------------------------------------------------------
#include <DirectXMath.h>
#include "Direct3D11.h"
#include "OBJLoader.h"
#include "ShaderLoader.h"
#include "TextureLoader.h"

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

	/// @name 描画
	//@{
	void render(const DirectX::XMFLOAT3X3& aTransform);
	//@}

	/// @name OBJとシェーダーを設定する
	//@{
	void setObjAndShaderData(const char* aOBJFileName, const char* aShaderFileName);
	//@}

private:
	/// @name プライベートメンバ変数
	//@{
	/// Direct3D11
	Direct3D11* mD3D11;
	/// TextureLoader
	TextureLoader* mTex;
	/// OBJデータ
	OBJData* mOBJData;
	/// シェーダーデータ
	ShaderData* mShaderData;
	//@}

};

} // namespace
// EOF
