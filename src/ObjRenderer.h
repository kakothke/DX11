#pragma once

//-------------------------------------------------------------------------------------------------
#include <DirectXMath.h>
#include "Direct3D11.h"
#include "OBJLoader.h"
#include "ShaderLoader.h"

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

	/// @name 描画設定
	//@{
	/// OBJを設定する
	void setOBJ(const LPCSTR aFileName);
	/// シェーダーを設定する
	void setShader(const LPCSTR aFileName);
	//@}

private:
	/// @name プライベートメンバ変数
	//@{
	/// OBJデータ
	OBJLoader::OBJData* mOBJData;
	/// シェーダーデータ
	ShaderLoader::ShaderData* mShaderData;
	//@}

};

} // namespace
// EOF
