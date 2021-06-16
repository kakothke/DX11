#pragma once

//-------------------------------------------------------------------------------------------------
#include "FontLoader.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

class FontRenderer
{
public:
	FontRenderer();
	~FontRenderer();

	void draw(const LPCTSTR aString, const LPCTSTR aFontName = NULL);

private:
	bool cretaeTexture();
	LPCTSTR mString;
	LPCTSTR mFontName;

};

} // namespace
// EOF
