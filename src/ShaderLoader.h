#pragma once

//-------------------------------------------------------------------------------------------------
#include <d3d11.h>
#include <d3dcompiler.h>
#include <unordered_map>
#include "Singleton.h"

//-------------------------------------------------------------------------------------------------
#pragma comment(lib, "d3dcompiler.lib")

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// シェーダー構造体
struct ShaderData
{
	ID3D11VertexShader* vs;
	ID3D11PixelShader* ps;
	ID3D11InputLayout* inputLayout;
	~ShaderData()
	{
		if (vs) {
			vs->Release();
			vs = nullptr;
		}
		if (ps) {
			ps->Release();
			ps = nullptr;
		}
		if (inputLayout) {
			inputLayout->Release();
			inputLayout = nullptr;
		}
	}
};

/// シェーダーデータ読み込みクラス
class ShaderLoader : public Singleton<ShaderLoader>
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	ShaderLoader();
	~ShaderLoader();
	//@}

	/// @name シェーダーを読み込む
	//@{
	bool load(const char* const aFileName);
	//@}

	/// @name アクセサ
	//@{
	/// シェーダーデータを取得する
	ShaderData* getShaderData(const char* const aFileName);
	//@}

private:
	/// @name 内部実装
	//@{
	/// 頂点シェーダーを作成する
	bool createVertexShader(const char* const aFileName);
	/// 入力レイアウトを作成する
	bool createInputLayout(const char* const aFileName);
	/// リフレクション内のDXGIFormatを検索する
	DXGI_FORMAT getDxgiFormat(D3D11_SIGNATURE_PARAMETER_DESC aParamDesc);
	/// ピクセルシェーダーを作成する
	bool createPixelShader(const char* const aFileName);
	//@}

	/// @name プライベートメンバ変数
	//@{
	/// シェーダー構造体
	std::unordered_map<const char*, ShaderData> mShaderData;
	//@}

};

} // namespace
// EOF
