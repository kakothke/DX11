#include "ResourceManager.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"

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
	result = OBJLoader::getInst()->load(ResourceFileName::OBJ.at(OBJList::Cube));
	result = OBJLoader::getInst()->load(ResourceFileName::OBJ.at(OBJList::Sphere));
	result = OBJLoader::getInst()->load(ResourceFileName::OBJ.at(OBJList::SkyBox));
	result = OBJLoader::getInst()->load(ResourceFileName::OBJ.at(OBJList::Test));

	// Sprites
	result = SpriteLoader::getInst()->load(ResourceFileName::Sprite.at(SpriteList::Test));

	// Shaders
	result = ShaderLoader::getInst()->load(ResourceFileName::Shader.at(ShaderList::Unlit));
	result = ShaderLoader::getInst()->load(ResourceFileName::Shader.at(ShaderList::Standard));
	result = ShaderLoader::getInst()->load(ResourceFileName::Shader.at(ShaderList::Sprite));
	result = ShaderLoader::getInst()->load(ResourceFileName::Shader.at(ShaderList::SkyBox));

	return result;
}

} // namespace
// EOF
