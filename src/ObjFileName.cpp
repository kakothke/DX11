#include "ObjFileName.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
/// obj�t�@�C������Ԃ�
/// @param aObjList �ǂݍ��݂���obj���w�肷��
/// @return �t�@�C���p�X
const char* ObjFileName::fileName(ObjList aObjList)
{
	return mFileName[aObjList];
}

//-------------------------------------------------------------------------------------------------
// obj�t�@�C�����̏�����
std::unordered_map<ObjList, const char*> ObjFileName::mFileName = {
	{ObjList::Cube  , "res/mesh/cube.obj"  },
	{ObjList::Sphere, "res/mesh/sphere.obj"}
};

} // namespace
// EOF
