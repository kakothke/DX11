#pragma once

//-------------------------------------------------------------------------------------------------
#include <unordered_map>

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// シェーダーリスト
enum class ShaderList
{
	Unlit,
	Standard
};

/// シェーダーファイル名取得用クラス
class ShaderFileName
{
public:
	/// 指定したシェーダーのファイルパスを取得する
	/// @param aList 取得したいシェーダーファイルを指定する列挙型
	/// @return ファイルパス
	inline static const char* fileName(ShaderList aList)
	{
		return mFileName[aList];
	}

private:
	ShaderFileName();
	static std::unordered_map<ShaderList, const char*> mFileName;

};

} // namespace
// EOF
