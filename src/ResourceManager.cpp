#include "ResourceManager.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
const static auto OBJ_LOADER = OBJLoader::getInst();
const static auto SPRITE_LOADER = SpriteLoader::getInst();
const static auto SHADER_LOADER = ShaderLoader::getInst();
const static auto SOUND = Sound::getInst();
const static auto FONT_LOADER = FontLoader::getInst();

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
ResourceManager::ResourceManager()
{
}

//-------------------------------------------------------------------------------------------------
/// デストラクタ
ResourceManager::~ResourceManager()
{
}

//-------------------------------------------------------------------------------------------------
/// 初期読み込み
void ResourceManager::initialize()
{
	// OBJs
	OBJ_LOADER->load(ResourceFileName::OBJ.at(OBJList::Boss));
	OBJ_LOADER->load(ResourceFileName::OBJ.at(OBJList::Player));
	OBJ_LOADER->load(ResourceFileName::OBJ.at(OBJList::SkyBox));

	// Sprites
	SPRITE_LOADER->load(ResourceFileName::Sprite.at(SpriteList::Test));

	// Shaders
	SHADER_LOADER->load(ResourceFileName::Shader.at(ShaderList::Unlit));
	SHADER_LOADER->load(ResourceFileName::Shader.at(ShaderList::Standard));
	SHADER_LOADER->load(ResourceFileName::Shader.at(ShaderList::Sprite));
	SHADER_LOADER->load(ResourceFileName::Shader.at(ShaderList::SkyBox));

	// BGM
	mBGMHandle[BGMList::Test] = SOUND->load(ResourceFileName::BGM.at(BGMList::Test));
	SOUND->setLoop(mBGMHandle[BGMList::Test], true, 2);
	SOUND->setLoopPos(mBGMHandle[BGMList::Test], 855273, 2565818);

	// SE
	mSEHandle[SEList::Test] = SOUND->load(ResourceFileName::SE.at(SEList::Test));

	// Font
	FONT_LOADER->load(TEXT("あんずもじ湛"), TEXT("res/font/APJapanesefontF.ttf"));

}

//-------------------------------------------------------------------------------------------------
const int& ResourceManager::BGMHandle(const BGMList& aList) const
{
	return mBGMHandle.at(aList);
}

//-------------------------------------------------------------------------------------------------
const int& ResourceManager::SEHandle(const SEList& aList) const
{
	return mSEHandle.at(aList);
}

} // namespace
// EOF
