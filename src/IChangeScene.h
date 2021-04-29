#pragma once

//-------------------------------------------------------------------------------------------------
#include "SceneList.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// �V�[���J�ڃC���^�[�t�F�[�X
class IChangeScene
{
public:
	IChangeScene() = default;
	virtual ~IChangeScene() = default;
	virtual void changeScene(const SceneList aSceneList) = 0;

};

} // namespace
// EOF
