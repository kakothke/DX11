#pragma once

//-------------------------------------------------------------------------------------------------
#include <unordered_map>
#include "ShaderList.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// objファイル名取得用クラス
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
