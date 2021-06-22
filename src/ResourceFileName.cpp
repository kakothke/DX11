#include "ResourceFileName.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// OBJ
const std::unordered_map<OBJList, const char*> ResourceFileName::OBJ =
{
	{ OBJList::Player, "res/mesh/player/Player.obj" },
	{ OBJList::Boss, "res/mesh/boss/EnemyBox.obj" },
	{ OBJList::SkyBox, "res/mesh/skybox/SkyBox.obj" },
	{ OBJList::Kabocha, "res/mesh/kabocha/kabocha.obj" },
};

/// Sprite
const std::unordered_map<SpriteList, const char*> ResourceFileName::Sprite =
{
	{ SpriteList::Test, "res/img/kao.png" },
};

/// Shader
const std::unordered_map<ShaderList, const char*> ResourceFileName::Shader =
{
	{ ShaderList::Unlit, "hlsl/Unlit.hlsl" },
	{ ShaderList::Standard, "hlsl/Standard.hlsl" },
	{ ShaderList::Sprite, "hlsl/Sprite.hlsl" },
	{ ShaderList::SkyBox, "hlsl/SkyBox.hlsl" },
};

/// BGM
const std::unordered_map<BGMList, const char*> ResourceFileName::BGM =
{
	{ BGMList::Test, "res/bgm/music_0.wav" },
};

/// SE
const std::unordered_map<SEList, const char*> ResourceFileName::SE =
{
	{ SEList::Test, "res/se/test.wav" },
};

} // namespace
// EOF
