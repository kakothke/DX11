#pragma once

//-------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <unordered_map>
#include "Singleton.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

struct FontData
{
	HDC hdc;
	HFONT oldFont;
	LPCTSTR fileName;
};

/// ƒtƒHƒ“ƒg
class FontLoader : public Singleton<FontLoader>
{
public:
	FontLoader();
	~FontLoader();

	bool load(const LPCTSTR aFontName, const LPCTSTR aFileName = NULL);
	const HDC hdc(const LPCTSTR aFontName);

private:
	std::unordered_map<LPCTSTR, FontData> mFontData;

};

} // namespace
// EOF
