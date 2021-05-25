#pragma once

//-------------------------------------------------------------------------------------------------
#include <d3d11.h>
#include <unordered_map>
#include "Singleton.h"
#include "VertexShader.h"
#include "PixelShader.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// シェーダー構造体
struct ShaderData
{
	VertexShader vs;
	PixelShader ps;
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

	/// @name シェーダーを作成する
	//@{
	bool load(const char* aFileName);
	//@}

	/// @name アクセサ
	//@{
	/// シェーダーデータを取得する
	ShaderData* getShaderData(const char* aFileName);
	//@}

private:
	/// @name プライベートメンバ変数
	//@{
	/// シェーダー構造体
	std::unordered_map<const char*, ShaderData> mShaderData;
	//@}

};

} // namespace
// EOF
