#pragma once

//-------------------------------------------------------------------------------------------------
#include <d3d11.h>
#include <d3dcompiler.h>
#include <unordered_map>

//-------------------------------------------------------------------------------------------------
#pragma comment(lib, "d3dcompiler.lib")

//-------------------------------------------------------------------------------------------------
namespace DX11 {

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
class ShaderLoader
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	ShaderLoader();
	~ShaderLoader();
	//@}

	/// @name シェーダーを作成する
	//@{
	bool load(const char* const aFileName);
	//@}

	/// @name アクセサ
	//@{
	/// シェーダーデータを取得する
	ShaderData* getShaderData(const char* const aFileName);
	//@}

private:
	bool createVertexShader(const char* const aFileName);
	bool createInputLayout(const char* const aFileName);
	DXGI_FORMAT getDxgiFormat(D3D11_SIGNATURE_PARAMETER_DESC aParamDesc);
	bool createPixelShader(const char* const aFileName);

	/// @name プライベートメンバ変数
	//@{
	/// シェーダー構造体
	std::unordered_map<const char*, ShaderData> mShaderData;
	//@}

};

} // namespace
// EOF
