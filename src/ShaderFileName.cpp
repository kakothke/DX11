#include "ShaderFileName.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

std::unordered_map<ShaderList, const char*> ShaderFileName::mFileName =
{
	{ ShaderList::Unlit, "shader/Unlit.hlsl" },
	{ ShaderList::Standard, "shader/Standard.hlsl" },
};

} // namespace
// EOF
