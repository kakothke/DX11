#pragma once

//-------------------------------------------------------------------------------------------------
#include <unordered_map>

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// objリスト
enum class ObjList
{
	Cube,
	Sphere,

	TERM
};

/// objファイルパス
class ObjFilePath
{
public:
	/// @brief objファイルパスを返す
	/// @param aObjList 読み込みたいobjを指定する
	/// @return ファイルパス
	inline static const char* filePath(ObjList aObjList)
	{
		return mFilePath[aObjList];
	}

private:
	ObjFilePath();
	static std::unordered_map<ObjList, const char*> mFilePath;

};

// objファイルパスを指定
std::unordered_map<ObjList, const char*> ObjFilePath::mFilePath = {
	{ObjList::Cube  , "res/mesh/cube.obj"  },
	{ObjList::Sphere, "res/mesh/sphere.obj"}
};

} // namespace
// EOF
