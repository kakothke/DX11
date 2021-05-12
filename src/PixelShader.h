#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseShader.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// ピクセルシェーダー
class PixelShader : public BaseShader
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	PixelShader();
	~PixelShader();
	//@}

	/// @name シェーダーを作成する
	//@{
	bool create(const char* aFileName) override;
	//@}

	/// @name アクセサ
	//@{
	/// インターフェースを返す
	ID3D11PixelShader* getInterface() const;
	//@}

protected:
	/// @name プライベートメンバ変数
	//@{
	/// インターフェース
	ID3D11PixelShader* mInterface;
	//@}

};

} // namespace
// EOF
