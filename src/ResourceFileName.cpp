#include "ResourceFileName.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// OBJ
const std::unordered_map<OBJList, const char*> ResourceFileName::OBJ =
{
	{ OBJList::Cube, "res/mesh/ground/Ground.obj "},
	{ OBJList::Obstract, "res/mesh/obstract/Obstract.obj "},
	{ OBJList::Player, "res/mesh/pencilMissile/PencilMissile.obj" },
	{ OBJList::Boss, "res/mesh/boss/EnemyBox.obj" },
	{ OBJList::SkyBox, "res/mesh/skybox/SkyBox.obj" },
	{ OBJList::Kabocha, "res/mesh/kabocha/kabocha.obj" },
};

/// Sprite
const std::unordered_map<SpriteList, const char*> ResourceFileName::Sprite =
{
	{ SpriteList::UI_Arrow, "res/img/arrow.png" },
	{ SpriteList::Efect_Booster, "res/img/booster.png" },
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
