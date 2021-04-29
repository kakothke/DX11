#pragma once

//-------------------------------------------------------------------------------------------------
#include <stack>
#include <memory>

#include "SceneList.h"
#include "IChangeScene.h"
#include "AbstractScene.h"

//-------------------------------------------------------------------------------------------------
namespace DX11{

/// シーン管理
class SceneManager : public IChangeScene
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	SceneManager();
	~SceneManager();
	//@}

	/// @name 動作
	//@{
	void run();
	//@}

	/// @name シーン遷移
	//@{
	void changeScene(const SceneList aSceneList) override;
	//@}

private:
	/// @name プライベートメンバ変数
	//@{
	/// シーンのスタック
	std::stack<std::shared_ptr<AbstractScene>> mSceneStack;
	//@}

};

} // namespace
// EOF
