#pragma once

//-------------------------------------------------------------------------------------------------
#include <d3d11.h>
#include <unordered_map>
#include <DirectXMath.h>
#include "Singleton.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// テクスチャー読み込みクラス
class TextureLoader : public Singleton<TextureLoader>
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	TextureLoader();
	~TextureLoader();
	//@}

	/// @name シェーダーを作成する
	//@{
	bool load(const LPCSTR aFileName);
	void release(const LPCSTR aFileName);
	//@}

	/// @name アクセサ
	//@{
	/// テクスチャーを取得する
	ID3D11ShaderResourceView* getTexture(const LPCSTR aFileName) const;
	/// テクスチャーのサイズを取得する
	const DirectX::XMFLOAT2 getTextureSize(const LPCSTR aFileName) const;
	//@}

private:
	/// @name プライベートメンバ変数
	//@{
	/// テクスチャー
	std::unordered_map<std::string, ID3D11ShaderResourceView*> mTexture;
	//@}

};

} // namespace
// EOF
