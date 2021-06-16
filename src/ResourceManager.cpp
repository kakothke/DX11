#include "ResourceManager.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"
#include "OBJLoader.h"
#include "SpriteLoader.h"
#include "ShaderLoader.h"
#include "Sound.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
ResourceManager::ResourceManager()
{
}

//-------------------------------------------------------------------------------------------------
ResourceManager::~ResourceManager()
{
}

//-------------------------------------------------------------------------------------------------
bool ResourceManager::initialize()
{
	bool result;

	// OBJs
	auto obj = OBJLoader::getInst();
	result = obj->load(ResourceFileName::OBJ.at(OBJList::Cube));
	result = obj->load(ResourceFileName::OBJ.at(OBJList::Sphere));
	result = obj->load(ResourceFileName::OBJ.at(OBJList::SkyBox));
	result = obj->load(ResourceFileName::OBJ.at(OBJList::Test));

	// Sprites
	auto sprite = SpriteLoader::getInst();
	result = sprite->load(ResourceFileName::Sprite.at(SpriteList::Test));

	// Shaders
	auto shader = ShaderLoader::getInst();
	result = shader->load(ResourceFileName::Shader.at(ShaderList::Unlit));
	result = shader->load(ResourceFileName::Shader.at(ShaderList::Standard));
	result = shader->load(ResourceFileName::Shader.at(ShaderList::Sprite));
	result = shader->load(ResourceFileName::Shader.at(ShaderList::SkyBox));

	// Sound


	return result;
}

} // namespace
// EOF
