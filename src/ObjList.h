#pragma once

//-------------------------------------------------------------------------------------------------
#include <unordered_map>

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// obj���X�g
enum class ObjList
{
	Cube,
	Sphere,

	TERM
};

/// obj�t�@�C���p�X
class ObjFilePath
{
public:
	/// @brief obj�t�@�C���p�X��Ԃ�
	/// @param aObjList �ǂݍ��݂���obj���w�肷��
	/// @return �t�@�C���p�X
	inline static const char* filePath(ObjList aObjList)
	{
		return mFilePath[aObjList];
	}

private:
	ObjFilePath();
	static std::unordered_map<ObjList, const char*> mFilePath;

};

// obj�t�@�C���p�X���w��
std::unordered_map<ObjList, const char*> ObjFilePath::mFilePath = {
	{ObjList::Cube  , "res/mesh/cube.obj"  },
	{ObjList::Sphere, "res/mesh/sphere.obj"}
};

} // namespace
// EOF
