#include "ShaderFileName.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

std::unordered_map<ShaderList, const char*> ShaderFileName::mFileName =
{
	{ ShaderList::UnlitShader, "res/shader/UnlitShader" },
};

} // namespace
// EOF
