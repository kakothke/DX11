#include "SpriteFileName.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

std::unordered_map<SpriteList, const char*> SpriteFileName::mFileName =
{
	{ SpriteList::TestImage, "res/texture/test1.png" },
};

} // namespace
// EOF
