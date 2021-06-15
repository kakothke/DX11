#pragma once

//-------------------------------------------------------------------------------------------------
#include "SceneList.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

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
