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
	// �f�t�H���g�t�H���g�쐬
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
	// �t�H���g���\�[�X�̓ǂݍ���
	if (aFileName) {
		if (!AddFontResourceEx(aFileName, FR_PRIVATE, NULL)) {
			return false;
		}
	}

	// �t�H���g�̐���
	LOGFONT lf = {
		256,
		0, 0, 0, 0, 0, 0, 0,
		SHIFTJIS_CHARSET,
		OUT_TT_ONLY_PRECIS,
		CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY,
		DEFAULT_PITCH | FF_MODERN,
		TEXT("�l�r �o����")// �e�X�g
	};
	HFONT hFont = CreateFontIndirect(&lf);
	if (hFont == NULL) {
		return false;
	}

	// �f�o�C�X�ɓo�^
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
