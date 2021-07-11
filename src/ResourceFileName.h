#pragma once

//-------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <unordered_map>

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// OBJ
enum class OBJList
{
	Cube,
	Obstract,
	Player,
	Boss,
	SkyBox,
	Kabocha,
};

/// Sprite
enum class SpriteList
{
	UI_Arrow,
	UI_TitleLogo,
	UI_Start,
	UI_Black,
	Efect_Booster,
	Efect_Graze,
};

/// Shader
enum class ShaderList
{
	Unlit,
	Standard,
	Sprite,
	SkyBox,
};

/// BGM
enum class SoundList
{
	BGM_00,
	SE_Shot,
	SE_Graze,
	SE_Start,
};

/// リソースファイル名取得用クラス
class ResourceFileName
{
public:
	const static std::unordered_map<OBJList, const char*> OBJ;
	const static std::unordered_map<SpriteList, const char*> Sprite;
	const static std::unordered_map<ShaderList, const char*> Shader;
	const static std::unordered_map<SoundList, const char*> Sound;

};


} // namespace
// EOF
