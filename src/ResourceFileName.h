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
	Player,
	Boss,
	SkyBox,
	Kabocha,
	Test,
};

/// Sprite
enum class SpriteList
{
	Test,
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
