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
	bool load(const char* const aFileName);
	void release(const char* const aFileName);
	//@}

	/// @name アクセサ
	//@{
	/// テクスチャーを取得する
	ID3D11ShaderResourceView* getTexture(const char* const aFileName);
	/// テクスチャーのサイズを取得する
	const DirectX::XMFLOAT2 getTextureSize(const char* const aFileName);
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
