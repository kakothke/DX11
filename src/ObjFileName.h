#pragma once

//-------------------------------------------------------------------------------------------------
#include <unordered_map>

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// OBJ���X�g
enum class OBJList
{
	Cube,
	Sphere,
	TestObj
};

/// OBJ�t�@�C�����擾�p�N���X
class OBJFileName
{
public:
	/// �w�肵��OBJ�̃t�@�C���p�X���擾����
	/// @param aList �擾������OBJ�t�@�C�����w�肷��񋓌^
	/// @return �t�@�C���p�X
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
