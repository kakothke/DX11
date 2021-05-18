#include "OBJFileName.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
/// 指定したOBJのファイルパスを取得する
/// @param aOBJList 取得したいOBJファイルを指定する列挙型
/// @return ファイルパス
const char* OBJFileName::fileName(OBJList aOBJList)
{
	return mFileName[aOBJList];
}

//-------------------------------------------------------------------------------------------------
// OBJファイルパスの指定
std::unordered_map<OBJList, const char*> OBJFileName::mFileName = {
	{OBJList::Cube  , "res/mesh/cube.obj"  },
	{OBJList::Sphere, "res/mesh/sphere.obj"}
};

} // namespace
// EOF
