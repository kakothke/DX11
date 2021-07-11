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
	{ SpriteList::UI_TitleLogo, "res/img/logo.png" },
	{ SpriteList::UI_Start, "res/img/start.png" },
	{ SpriteList::UI_Black, "res/img/black.png" },
	{ SpriteList::Efect_Booster, "res/img/booster.png" },
	{ SpriteList::Efect_Graze, "res/img/graze.png" },
};

/// Shader
const std::unordered_map<ShaderList, const char*> ResourceFileName::Shader =
{
	{ ShaderList::Unlit, "hlsl/Unlit.hlsl" },
	{ ShaderList::Standard, "hlsl/Standard.hlsl" },
	{ ShaderList::Sprite, "hlsl/Sprite.hlsl" },
	{ ShaderList::SkyBox, "hlsl/SkyBox.hlsl" },
};

/// Sound
const std::unordered_map<SoundList, const char*> ResourceFileName::Sound =
{
	{ SoundList::BGM_00, "res/bgm/music_0.wav" },
	{ SoundList::SE_Shot, "res/se/shot.wav" },
	{ SoundList::SE_Graze, "res/se/graze.wav" },
	{ SoundList::SE_Start, "res/se/start.wav" },
};

} // namespace
// EOF
