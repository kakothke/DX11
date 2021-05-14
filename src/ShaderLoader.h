#pragma once

//-------------------------------------------------------------------------------------------------
#include <D3D11.h>
#include <unordered_map>
#include "Singleton.h"
#include "ShaderList.h"
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
	bool load(ShaderList aList);
	//@}

	/// @name アクセサ
	//@{
	/// シェーダー構造体を返す
	ShaderData* getShaderData(ShaderList aList);
	//@}

private:
	/// @name プライベートメンバ変数
	//@{
	/// シェーダー構造体
	std::unordered_map<ShaderList, ShaderData> mShaderData;
	//@}

};

} // namespace
// EOF
