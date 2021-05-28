#include "OBJFileName.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

std::unordered_map<OBJList, const char*> OBJFileName::mFileName =
{
	{ OBJList::Cube, "res/mesh/cube.obj" },
	{ OBJList::Sphere, "res/mesh/sphere.obj" },
	{ OBJList::TestObj, "res/mesh/test/kirby.obj" }
};

} // namespace
// EOF
