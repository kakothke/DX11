#pragma once

//-------------------------------------------------------------------------------------------------
#include <unordered_map>
#include "ShaderList.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// obj�t�@�C�����擾�p�N���X
class ShaderFileName
{
public:
	static const char* fileName(ShaderList aShaderList);

private:
	ShaderFileName();
	static std::unordered_map<ShaderList, const char*> mFileName;

};

} // namespace
// EOF
