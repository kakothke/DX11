#pragma once

//-------------------------------------------------------------------------------------------------
#include <unordered_map>
#include "Singleton.h"

//-------------------------------------------------------------------------------------------------
#include "ResourceFileName.h"
#include "OBJLoader.h"
#include "SpriteLoader.h"
#include "ShaderLoader.h"
#include "Sound.h"
#include "FontLoader.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// リソース管理クラス
class ResourceManager : public Singleton<ResourceManager>
{
public:
	ResourceManager();
	~ResourceManager();

	void initialize();

	const int& BGMHandle(const BGMList& aList) const;
	const int& SEHandle(const SEList& aList) const;

private:
	std::unordered_map<BGMList, int> mBGMHandle;
	std::unordered_map<SEList, int> mSEHandle;

};

} // namespace
// EOF
