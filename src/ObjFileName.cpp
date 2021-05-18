#include "OBJFileName.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
/// �w�肵��OBJ�̃t�@�C���p�X���擾����
/// @param aOBJList �擾������OBJ�t�@�C�����w�肷��񋓌^
/// @return �t�@�C���p�X
const char* OBJFileName::fileName(OBJList aOBJList)
{
	return mFileName[aOBJList];
}

//-------------------------------------------------------------------------------------------------
// OBJ�t�@�C���p�X�̎w��
std::unordered_map<OBJList, const char*> OBJFileName::mFileName = {
	{OBJList::Cube  , "res/mesh/cube.obj"  },
	{OBJList::Sphere, "res/mesh/sphere.obj"}
};

} // namespace
// EOF
