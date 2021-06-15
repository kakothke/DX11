#pragma once

//-------------------------------------------------------------------------------------------------
#include <stack>
#include <memory>

#include "SceneList.h"
#include "IChangeScene.h"
#include "AbstractScene.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK{

/// シーン管理
class SceneManager : public IChangeScene
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	SceneManager();
	~SceneManager();
	//@}

	/// @name 更新/描画
	//@{
	void update();
	void draw();
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
