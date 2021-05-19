#pragma once

//-------------------------------------------------------------------------------------------------
#include <unordered_map>

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// OBJリスト
enum class OBJList
{
	Cube,
	Sphere,
	TestObj
};

/// OBJファイル名取得用クラス
class OBJFileName
{
public:
	/// 指定したOBJのファイルパスを取得する
	/// @param aList 取得したいOBJファイルを指定する列挙型
	/// @return ファイルパス
	inline static const char* fileName(OBJList aList)
	{
		return mFileName[aList];
	}

private:
	OBJFileName();
	static std::unordered_map<OBJList, const char*> mFileName;

};

} // namespace
// EOF
