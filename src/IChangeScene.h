#pragma once

//-------------------------------------------------------------------------------------------------
#include "SceneList.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// シーン遷移インターフェース
class IChangeScene
{
public:
	IChangeScene() = default;
	virtual ~IChangeScene() = default;
	virtual void changeScene(const SceneList aSceneList) = 0;

};

} // namespace
// EOF
