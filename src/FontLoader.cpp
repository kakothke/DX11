#include "FontLoader.h"

//-------------------------------------------------------------------------------------------------
#include <Shlwapi.h>
#include <codecvt>

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
const static LPCTSTR DEFAULT_FONT = TEXT("�l�r�@�S�V�b�N");

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
FontLoader::FontLoader()
	: mFontData()
{
	mFontData.clear();
	// �f�t�H���g�t�H���g�쐬
	load(DEFAULT_FONT);
}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
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
/// �t�H���g��ǂݍ���
/// @param aFontName �t�H���g��
/// @param aFileName �t�@�C���p�X
/// @return ���� ����(true)
bool FontLoader::load(const LPCTSTR aFontName, const LPCTSTR aFileName)
{
	// �t�H���g���\�[�X�̓ǂݍ���
	if (aFileName) {
		if (!AddFontResourceEx(aFileName, FR_PRIVATE, NULL)) {
			return false;
		}
	}

	// �����R�[�h�擾
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

	// �t�H���g�̐���
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

	// �f�o�C�X�ɓo�^
	mFontData[aFontName].hdc = GetDC(NULL);
	mFontData[aFontName].oldFont = (HFONT)SelectObject(mFontData[aFontName].hdc, hFont);
	mFontData[aFontName].fileName = aFileName;

	return true;
}

//-------------------------------------------------------------------------------------------------
/// HDC���擾����
/// @param aFontName �t�H���g��
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