#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"
#include "GameObjectTag.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// 全てのゲームオブジェクトの基底クラス
class Camera : public BaseGameObject
{
private:
	struct ViewMatrix
	{
		Vector3 pos;
		Vector3 forcus;
		Vector3 up;
		ViewMatrix()
			: pos(0, 0, -50.0f)
			, forcus(0, 0, 0)
			, up(0, 1.0f, 0)
		{
		}
	};
	struct WorldMatrix
	{
		float fov;
		float nearZ;
		float farZ;
		WorldMatrix()
			: fov(45.0f)
			, nearZ(0.1f)
			, farZ(100.0f)
		{
		}
	};

public:
	/// @name コンストラクタ
	//@{
	Camera();
	Camera(ViewMatrix aView);
	Camera(WorldMatrix aWorld);
	Camera(ViewMatrix aView, WorldMatrix aWorld);
	//@}

	/// @name 更新/描画
	//@{
	void update() override;
	void draw() override;
	//@}


protected:
	/// @name プロテクテッドメンバ関数
	//@{
	void setUpTransform();
	//@}

	/// @name プロテクテッドメンバ変数
	//@{
	ViewMatrix mView;
	WorldMatrix mWorld;
	//@}

};

} // namespace
// EOF
