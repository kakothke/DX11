#include "ObjFileName.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
/// objファイル名を返す
/// @param aObjList 読み込みたいobjを指定する
/// @return ファイルパス
const char* ObjFileName::fileName(ObjList aObjList)
{
	return mFileName[aObjList];
}

//-------------------------------------------------------------------------------------------------
// objファイル名の初期化
std::unordered_map<ObjList, const char*> ObjFileName::mFileName = {
	{ObjList::Cube  , "res/mesh/cube.obj"  },
	{ObjList::Sphere, "res/mesh/sphere.obj"}
};

} // namespace
// EOF
