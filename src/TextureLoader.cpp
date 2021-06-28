#include "TextureLoader.h"

//-------------------------------------------------------------------------------------------------
#include <WICTextureLoader11.h>
#include <codecvt>
#include "Direct3D11.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
TextureLoader::TextureLoader()
	: mTexture()
{
}

//-------------------------------------------------------------------------------------------------
/// デストラクタ
TextureLoader::~TextureLoader()
{
	for (auto tex : mTexture) {
		if (tex.second) {
			tex.second->Release();
			tex.second = nullptr;
		}
	}
}

//-------------------------------------------------------------------------------------------------
/// テクスチャを作成する
/// @param aFileName ファイルパス
/// @return 結果 成功(true)
bool TextureLoader::load(const LPCSTR aFileName)
{
	if (mTexture.count(aFileName)) {
		// テクスチャーは二重読み込みのエラー告知をしない
		return false;
	}

	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> cv;
	std::wstring wFileName = cv.from_bytes(aFileName);

	HRESULT hr;
	const auto device = Direct3D11::getInst()->getDevice();
	hr = DirectX::CreateWICTextureFromFile(device, wFileName.c_str(), nullptr, &mTexture[aFileName]);
	if (FAILED(hr)) {
		MessageBox(nullptr, TEXT("テクスチャーの作成に失敗しました"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/// 破棄
/// @param aFileName ファイルパス
void TextureLoader::release(const LPCSTR aFileName)
{
	if (!mTexture.count(aFileName)) {
		MessageBox(nullptr, TEXT("存在しないテクスチャーを破棄しようとしています。"), TEXT("ERROR"), MB_OK | MB_ICONHAND);
		return;
	}
	mTexture[aFileName]->Release();
	mTexture[aFileName] = nullptr;
	mTexture.erase(aFileName);
}

//-------------------------------------------------------------------------------------------------
/// テクスチャーを取得する
/// @param aFileName ファイルパス
/// @return テクスチャー
ID3D11ShaderResourceView* TextureLoader::getTexture(const LPCSTR aFileName) const
{
	if (!mTexture.count(aFileName)) {
		// 描画時に毎フレーム呼ばれる処理なのでエラー告知はしない
		return nullptr;
	}
	return mTexture.at(aFileName);
}

//-------------------------------------------------------------------------------------------------
/// テクスチャーのサイズを取得する
const Vector2 TextureLoader::getTextureSize(const LPCSTR aFileName) const
{
	if (!mTexture.count(aFileName)) {
		return {
			0.0f,
			0.0f
		};
	}

	ID3D11Resource* res = nullptr;
	ID3D11Texture2D* tex2D = nullptr;
	D3D11_TEXTURE2D_DESC desc = {};
	mTexture.at(aFileName)->GetResource(&res);
	res->QueryInterface(&tex2D);
	tex2D->GetDesc(&desc);
	res->Release();
	res = nullptr;
	tex2D->Release();
	tex2D = nullptr;

	return {
		(float)desc.Width,
		(float)desc.Height
	};
}

} // namespace
// EOF
