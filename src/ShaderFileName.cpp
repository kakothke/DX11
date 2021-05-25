#include "ShaderFileName.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

std::unordered_map<ShaderList, const char*> ShaderFileName::mFileName =
{
	{ ShaderList::Unlit, "hlsl/Unlit.hlsl" },
	{ ShaderList::Standard, "hlsl/Standard.hlsl" },
};

} // namespace
// EOF
