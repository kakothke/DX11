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
	bool load(const LPCSTR aFileName);
	//@}

	/// @name 構造体
	//@{
	/// シェーダー構造体
	struct ShaderData
	{
		/// 頂点シェーダー
		ID3D11VertexShader* vs;
		/// ピクセルシェーダー
		ID3D11PixelShader* ps;
		/// 入力レイアウト
		ID3D11InputLayout* inputLayout;
		/// デストラクタ
		~ShaderData();
	};
	//@}

	/// @name アクセサ
	//@{
	/// シェーダーデータを取得する
	ShaderData* getShaderData(const LPCSTR aFileName);
	//@}

private:
	/// @name 内部実装
	//@{
	/// 頂点シェーダーを作成する
	bool createVertexShader(const LPCSTR aFileName);
	/// 入力レイアウトを作成する
	bool createInputLayout(const LPCSTR aFileName);
	/// リフレクション内のDXGIFormatを検索する
	DXGI_FORMAT getDxgiFormat(D3D11_SIGNATURE_PARAMETER_DESC aParamDesc);
	/// ピクセルシェーダーを作成する
	bool createPixelShader(const LPCSTR aFileName);
	//@}

	/// @name プライベートメンバ変数
	//@{
	/// シェーダー構造体
	std::unordered_map<LPCSTR, ShaderData> mShaderData;
	//@}

};

} // namespace
// EOF
