#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseShader.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// 頂点シェーダー
class VertexShader : public BaseShader
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	VertexShader();
	~VertexShader();
	//@}

	/// @name 頂点シェーダーを作成する
	//@{
	bool create(const char* aFileName) override;
	//@}

	/// @name アクセサ
	//@{
	/// インターフェースを返す
	const ID3D11VertexShader* shaderInterface() const;
	/// 入力レイアウトを返す
	const ID3D11InputLayout* inputLayout() const;
	//@}

private:
	/// @name 入力レイアウトを作成する
	//@{
	bool createInputLayout();
	//@}

	/// @name プライベートメンバ変数
	//@{
	/// インターフェース
	ID3D11VertexShader* mInterface;
	/// 入力レイアウト
	ID3D11InputLayout* mInputLayout;
	//@}

};

} // namespace
// EOF
