#include "ResourceManager.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

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
	const auto obj = OBJLoader::getInst();
	obj->load(ResourceFileName::OBJ.at(OBJList::Boss));
	obj->load(ResourceFileName::OBJ.at(OBJList::Player));
	obj->load(ResourceFileName::OBJ.at(OBJList::SkyBox));

	// Sprites
	const auto sprite = SpriteLoader::getInst();
	sprite->load(ResourceFileName::Sprite.at(SpriteList::Test));

	// Shaders
	const auto shader = ShaderLoader::getInst();
	shader->load(ResourceFileName::Shader.at(ShaderList::Unlit));
	shader->load(ResourceFileName::Shader.at(ShaderList::Standard));
	shader->load(ResourceFileName::Shader.at(ShaderList::Sprite));
	shader->load(ResourceFileName::Shader.at(ShaderList::SkyBox));

	// BGM
	const auto sound = Sound::getInst();
	mBGMHandle[BGMList::Test] = sound->load(ResourceFileName::BGM.at(BGMList::Test));
	sound->setLoop(mBGMHandle[BGMList::Test], true, 2);
	sound->setLoopPos(mBGMHandle[BGMList::Test], 855273, 2565818);

	// SE
	const auto font = FontLoader::getInst();
	mSEHandle[SEList::Test] = sound->load(ResourceFileName::SE.at(SEList::Test));

	// Font
	font->load(TEXT("あんずもじ湛"), TEXT("res/font/APJapanesefontF.ttf"));

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
