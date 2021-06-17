#pragma once

//-------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <unordered_map>
#include "Singleton.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// フォント読み込み
class FontLoader : public Singleton<FontLoader>
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	FontLoader();
	~FontLoader();
	//@}

	/// @name 読み込み
	//@{
	bool load(const LPCTSTR aFontName, const LPCTSTR aFileName = NULL);
	//@}

	/// @name アクセサ
	//@{
	/// HDCを取得する
	const HDC hdc(const LPCTSTR aFontName);
	//@}

private:
	/// @name 内部構造体
	//@{
	struct FontData
	{
		HDC hdc;
		HFONT oldFont;
		LPCTSTR fileName;
	};
	//@}

	/// @name プライベートメンバ変数
	//@{
	std::unordered_map<LPCTSTR, FontData> mFontData;
	//@}

};

} // namespace
// EOF
