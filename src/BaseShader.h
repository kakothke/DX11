#pragma once

//-------------------------------------------------------------------------------------------------
#include <d3d11.h>

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// シェーダ基底クラス
class BaseShader
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	BaseShader();
	virtual ~BaseShader();
	//@}

	/// @name 作成関数
	//@{
	/// シェーダを作成する
	virtual bool create(const char* aFileName) = 0;
	//@}

protected:
	/// @name データ読み込み
	//@{
	bool load(const char* aFileName);
	//@}

	/// @name プロテクテッドメンバ変数
	//@{
	/// シェーダデータ(バイナリ)
	char* mData;
	/// データのサイズ
	long mSize;
	//@}

};

} // namespace
// EOF
