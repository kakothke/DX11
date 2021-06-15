#pragma once

//-------------------------------------------------------------------------------------------------
#include <unordered_map>

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// OBJ
enum class OBJList
{
	Cube,
	Sphere,
	SkyBox,
	Test
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

/// リソースファイル名取得用クラス
class ResourceFileName
{
public:
	const static std::unordered_map<OBJList, const char*> OBJ;
	const static std::unordered_map<SpriteList, const char*> Sprite;
	const static std::unordered_map<ShaderList, const char*> Shader;

};


} // namespace
// EOF
