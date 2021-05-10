#pragma once
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

	/// @name アクセサ
	//@{
	/// シェーダのデータ（バイナリ）を返す
	const char* data() const;
	/// シェーダのデータサイズを返す
	const long size() const;
	//@}

protected:
	/// @name 読み込み
	//@{
	bool Load(const char* file_name);
	//@}

private:
	/// @name プライベートメンバ変数
	//@{
	/// シェーダデータ(バイナリ)
	char* mData;
	/// データのサイズ
	long mSize;
	//@}

};

} // namespace
// EOF
