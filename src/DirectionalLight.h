#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"
#include "GameObjectTag.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// 全てのゲームオブジェクトの基底クラス
class DirectionalLight : public BaseGameObject
{
public:
	/// @name コンストラクタ
	//@{
	DirectionalLight();
	//@}

	/// @name 更新/描画
	//@{
	void update() override;
	void draw() override;
	//@}


protected:
	void updateConstantBuffer();
	DirectX::XMFLOAT4 mColor;

};

} // namespace
// EOF
