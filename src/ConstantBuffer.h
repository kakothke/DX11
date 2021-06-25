#pragma once

//-------------------------------------------------------------------------------------------------
#include <d3d11.h>
#include <DirectXMath.h>
#include <unordered_map>
#include "Transform.h"
#include "Color.h"
#include "OBJLoader.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// コンスタントバッファ
class ConstantBuffer
{
private:
	/// @name 内部構造体
	//@{
	/// 変換行列
	struct CB_MATRIX
	{
		DirectX::XMFLOAT4X4 W;
		DirectX::XMFLOAT4X4 V;
		DirectX::XMFLOAT4X4 P;
	};
	/// スプライト
	struct CB_SPRITE
	{
		DirectX::XMFLOAT4X4 MATRIX_P;
		DirectX::XMFLOAT4X4 MATRIX_W;
		DirectX::XMINT4 SPLIT = { 1, 1, 1, 1 };
	};
	/// カメラ
	struct CB_CAMERA
	{
		DirectX::XMFLOAT4 POS;
	};
	/// ライト
	struct CB_DLIGHT
	{
		DirectX::XMFLOAT4 ANGLE;
		DirectX::XMFLOAT4 COL;
	};
	/// カラー
	struct CB_COLOR
	{
		DirectX::XMFLOAT4 COL0;
		DirectX::XMFLOAT4 COL1;
	};
	/// マテリアル
	struct CB_MATERIAL
	{
		DirectX::XMFLOAT4 A;
		DirectX::XMFLOAT4 D;
		DirectX::XMFLOAT4 S;
	};
	//@}

public:
	/// @name コンストラクタ/デストラクタ
	//@{
	ConstantBuffer();
	~ConstantBuffer();
	//@}

	/// @name 初期化
	//@{
	bool initialize(ID3D11Device* aDevice, ID3D11DeviceContext* aContext);
	//@}

	/// @name コンスタントバッファ制御
	//@{
	/// 変換行列
	void setMatrixW(const Transform& aTransform);
	void setMatrixV(const Transform& aTransform);
	void setMatrixP(const float& aFov, const float& aNearZ, const float& aFarZ);
	void updateMatrix();
	/// スプライト
	void setSpriteMatrixW(const Transform& aTransform, const Vector2& aPivot);
	void setSpriteMatrixP(const Vector2& aAnchor);
	void setSpriteSplit(const Vector2& aSplit);
	void updateSprite();
	/// カメラ
	void updateCamera(const Vector3& aPos);
	/// ディレクショナルライト
	void updateDLight(const Vector3& aAngle, const Color& aCol);
	/// カラー
	void updateColor(const Color& aCol0, const Color& aCol1);
	/// OBJマテリアル
	void updateMaterial(const OBJLoader::OBJMaterial& aMaterial);
	//@}

private:
	/// @name 内部列挙型
	//@{
	/// コンスタントバッファの種類
	enum BufferList
	{
		MATRIX,
		SPRITE,
		CAMERA,
		DLIGHT,
		COLOR,
		MATERIAL,
	};
	//@}

	/// @name プライベートメンバ変数
	//@{
	/// デバイスコンテキスト
	ID3D11DeviceContext* mContext;
	/// 各種コンスタントバッファをまとめた連想配列
	std::unordered_map<BufferList, ID3D11Buffer*> mBuffers;
	/// 各種バッファの構造体
	CB_MATRIX mMATRIX;
	CB_SPRITE mSPRITE;
	CB_CAMERA mCAMERA;
	CB_DLIGHT mDLIGHT;
	CB_COLOR mCOLOR;
	CB_MATERIAL mMATERIAL;
	//@}

};

} // namespace
// EOF
