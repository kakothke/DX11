#pragma once

//-------------------------------------------------------------------------------------------------
#include <unordered_map>

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// OBJ
enum class OBJList
{
	Cube,
	Sphere,
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
};

/// ���\�[�X�t�@�C�����擾�p�N���X
class ResourceFileName
{
public:
	const static std::unordered_map<OBJList, const char*> OBJ;
	const static std::unordered_map<SpriteList, const char*> Sprite;
	const static std::unordered_map<ShaderList, const char*> Shader;

};


} // namespace
// EOF