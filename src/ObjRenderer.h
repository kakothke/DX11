#pragma once

//-------------------------------------------------------------------------------------------------
#include <DirectXMath.h>
#include "Direct3D11.h"
#include "Transform.h"
#include "OBJLoader.h"
#include "ShaderLoader.h"
#include "Color.h"

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
	void render(const Transform& aTransform);
	//@}

	/// @name 描画設定
	//@{
	/// OBJを設定する
	void setOBJ(const LPCSTR aFileName);
	/// シェーダーを設定する
	void setShader(const LPCSTR aFileName);
	/// カラーを設定する 
	void setColor(const Color& aColor);
	//@}

private:
	/// @name プライベートメンバ変数
	//@{
	/// OBJデータ
	OBJLoader::OBJData* mOBJData;
	/// シェーダーデータ
	ShaderLoader::ShaderData* mShaderData;
	/// カラー
	Color mColor;
	//@}

};

} // namespace
// EOF
