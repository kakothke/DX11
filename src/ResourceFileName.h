#pragma once

//-------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <unordered_map>

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// OBJ
enum class OBJList
{
	Player,
	Boss,
	SkyBox,
	Kabocha
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
enum class BGMList
{
	Test,
};

/// SE
enum class SEList
{
	Test,
};

/// リソースファイル名取得用クラス
class ResourceFileName
{
public:
	const static std::unordered_map<OBJList, const char*> OBJ;
	const static std::unordered_map<SpriteList, const char*> Sprite;
	const static std::unordered_map<ShaderList, const char*> Shader;
	const static std::unordered_map<BGMList, const char*> BGM;
	const static std::unordered_map<SEList, const char*> SE;

};


} // namespace
// EOF
