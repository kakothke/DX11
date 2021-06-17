#include "FontLoader.h"

//-------------------------------------------------------------------------------------------------
#include <Shlwapi.h>
#include <codecvt>

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
const static LPCTSTR DEFAULT_FONT = TEXT("ＭＳ　ゴシック");

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
FontLoader::FontLoader()
	: mFontData()
{
	mFontData.clear();
	// デフォルトフォント作成
	load(DEFAULT_FONT);
}

//-------------------------------------------------------------------------------------------------
/// デストラクタ
FontLoader::~FontLoader()
{
	for (auto fontData : mFontData) {
		SelectObject(fontData.second.hdc, fontData.second.oldFont);
		ReleaseDC(NULL, fontData.second.hdc);
		RemoveFontResourceEx(fontData.second.fileName, FR_PRIVATE, NULL);
	}
	mFontData.clear();
}

//------------------------------------------------------------------------------------------------
/// フォントを読み込む
/// @param aFontName フォント名
/// @param aFileName ファイルパス
/// @return 結果 成功(true)
bool FontLoader::load(const LPCTSTR aFontName, const LPCTSTR aFileName)
{
	// フォントリソースの読み込み
	if (aFileName) {
		if (!AddFontResourceEx(aFileName, FR_PRIVATE, NULL)) {
			return false;
		}
	}

	// 文字コード取得
	UINT code = 0;
#if _UNICODE
	code = (UINT)*aFontName;
#else
	if (IsDBCSLeadByte(*aFontName)) {
		code = (BYTE)aFontName[0] << 8 | (BYTE)aFontName[1];
	} else {
		code = aFontName[0];
	}	
#endif

	// フォントの生成
	const int size = 256;
	LOGFONT lf = {
		size,
		0, 0, 0, 0, 0, 0, 0,
		SHIFTJIS_CHARSET,
		OUT_TT_ONLY_PRECIS,
		CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY,
		DEFAULT_PITCH | FF_MODERN,
		code
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
/// HDCを取得する
/// @param aFontName フォント名
/// @return HDC
const HDC FontLoader::hdc(const LPCTSTR aFontName)
{
	if (!mFontData.count(aFontName)) {
		return mFontData[DEFAULT_FONT].hdc;
	}
	return mFontData[aFontName].hdc;
}

} // namespace
// EOF
