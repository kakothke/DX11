#include "ShaderFileName.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
/// obj�t�@�C������Ԃ�
/// @param aObjList �ǂݍ��݂���obj���w�肷��
/// @return �t�@�C���p�X
const char* ShaderFileName::fileName(ShaderList aShaderList)
{
	return mFileName[aShaderList];
}

//-------------------------------------------------------------------------------------------------
// obj�t�@�C�����̏�����
std::unordered_map<ShaderList, const char*> ShaderFileName::mFileName = {
	{ShaderList::UnlitShader  , "res/shader/UnlitShader"},
};

} // namespace
// EOF
