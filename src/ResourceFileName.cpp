#include "ResourceFileName.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// OBJ
const std::unordered_map<OBJList, const char*> ResourceFileName::OBJ =
{
	{ OBJList::Cube, "res/mesh/cube.obj" },
	{ OBJList::Sphere, "res/mesh/sphere.obj" },
	{ OBJList::Test, "res/mesh/kabocha/kabocha.obj" },
};

/// Sprite
const std::unordered_map<SpriteList, const char*> ResourceFileName::Sprite =
{
	{ SpriteList::Test, "res/image/kao.png" },
};

/// Shader
const std::unordered_map<ShaderList, const char*> ResourceFileName::Shader =
{
	{ ShaderList::Unlit, "hlsl/Unlit.hlsl" },
	{ ShaderList::Standard, "hlsl/Standard.hlsl" },
	{ ShaderList::Sprite, "hlsl/Sprite.hlsl" },
};

} // namespace
// EOF
