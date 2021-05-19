#include "ShaderFileName.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

std::unordered_map<ShaderList, const char*> ShaderFileName::mFileName =
{
	{ ShaderList::Unlit, "res/shader/Unlit" },
	{ ShaderList::Standard, "res/shader/Standard" },
};

} // namespace
// EOF
