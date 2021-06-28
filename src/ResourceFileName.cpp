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
	{ SpriteList::Test, "res/img/test.png" },
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
const std::unordered_map<SoundList, const char*> ResourceFileName::Sound =
{
	{ SoundList::BGM_00, "res/bgm/music_0.wav" },
	{ SoundList::SE_Shot, "res/se/shot.wav" },
};

} // namespace
// EOF
