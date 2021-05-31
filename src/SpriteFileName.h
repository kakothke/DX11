#pragma once

//-------------------------------------------------------------------------------------------------
#include <unordered_map>

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// シェーダーリスト
enum class SpriteList
{
	TestImage,
};

/// シェーダーファイル名取得用クラス
class SpriteFileName
{
public:
	/// 指定したシェーダーのファイルパスを取得する
	/// @param aList 取得したいシェーダーファイルを指定する列挙型
	/// @return ファイルパス
	inline static const char* fileName(SpriteList aList)
	{
		return mFileName[aList];
	}

private:
	SpriteFileName();
	static std::unordered_map<SpriteList, const char*> mFileName;

};

} // namespace
// EOF
