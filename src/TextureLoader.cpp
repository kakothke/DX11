#include "TextureLoader.h"
#include <codecvt>

//-------------------------------------------------------------------------------------------------
#include <WICTextureLoader11.h>
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
bool TextureLoader::load(const char* const aFileName)
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
void TextureLoader::release(const char* const aFileName)
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
ID3D11ShaderResourceView* TextureLoader::getTexture(const char* const aFileName)
{
	if (!mTexture.count(aFileName)) {
		// 描画時に毎フレーム呼ばれる処理なのでエラー告知はしない
		return nullptr;
	}
	return mTexture[aFileName];
}

} // namespace
// EOF
