#include "FontLoader.h"

//-------------------------------------------------------------------------------------------------
#include <Shlwapi.h>
#include <codecvt>

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
FontLoader::FontLoader()
	: mFontData()
{
	mFontData.clear();
	// デフォルトフォント作成
	load(NULL);
}

//-------------------------------------------------------------------------------------------------
FontLoader::~FontLoader()
{
	for (auto fontData : mFontData) {
		SelectObject(fontData.second.hdc, fontData.second.oldFont);
		ReleaseDC(NULL, fontData.second.hdc);
		RemoveFontResourceEx(fontData.second.fileName, FR_PRIVATE, NULL);
	}
	mFontData.clear();
}

//-------------------------------------------------------------------------------------------------
bool FontLoader::load(const LPCTSTR aFontName, const LPCTSTR aFileName)
{
	// フォントリソースの読み込み
	if (aFileName) {
		if (!AddFontResourceEx(aFileName, FR_PRIVATE, NULL)) {
			return false;
		}
	}

	// フォントの生成
	LOGFONT lf = {
		256,
		0, 0, 0, 0, 0, 0, 0,
		SHIFTJIS_CHARSET,
		OUT_TT_ONLY_PRECIS,
		CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY,
		DEFAULT_PITCH | FF_MODERN,
		TEXT("ＭＳ Ｐ明朝")// テスト
	};
	HFONT hFont = CreateFontIndirect(&lf);
	if (hFont == NULL) {
		return false;
	}

	// デバイスに登録
	mFontData[aFontName].hdc = GetDC(NULL);
	mFontData[aFontName].oldFont = (HFONT)SelectObject(mFontData[aFontName].hdc, hFont);
	mFontData[aFontName].fileName = aFileName;

	return true;
}

//-------------------------------------------------------------------------------------------------
const HDC FontLoader::hdc(const LPCTSTR aFontName)
{
	if (!mFontData.count(aFontName)) {
		return mFontData[NULL].hdc;
	}
	return mFontData[aFontName].hdc;
}

} // namespace
// EOF
