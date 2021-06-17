#pragma once

//-------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <unordered_map>
#include "Singleton.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// �t�H���g�ǂݍ���
class FontLoader : public Singleton<FontLoader>
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	FontLoader();
	~FontLoader();
	//@}

	/// @name �ǂݍ���
	//@{
	bool load(const LPCTSTR aFontName, const LPCTSTR aFileName = NULL);
	//@}

	/// @name �A�N�Z�T
	//@{
	/// HDC���擾����
	const HDC hdc(const LPCTSTR aFontName);
	//@}

private:
	/// @name �����\����
	//@{
	struct FontData
	{
		HDC hdc;
		HFONT oldFont;
		LPCTSTR fileName;
	};
	//@}

	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	std::unordered_map<LPCTSTR, FontData> mFontData;
	//@}

};

} // namespace
// EOF
