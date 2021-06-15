#pragma once

//-------------------------------------------------------------------------------------------------
#include <d3d11.h>
#include <DirectXMath.h>
#include <unordered_map>
#include "OBJLoader.h"

namespace KDXK {

/// 行列
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
	DirectX::XMFLOAT4 PIVOT;
	DirectX::XMINT4 SPLIT;
};

/// カメラ
struct CB_CAMERA
{
	DirectX::XMFLOAT4 POS;
	DirectX::XMFLOAT4 ROT;
};

/// ライト
struct CB_DLIGHT
{
	DirectX::XMFLOAT4 ROT;
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

/// コンスタントバッファ
class ConstantBuffer
{
public:
	ConstantBuffer();
	~ConstantBuffer();

	bool create();

	// 変換行列
	void setMatrixW(const DirectX::XMFLOAT3X3& aTransform);
	void setMatrixVP(const DirectX::XMFLOAT3X3& aTransform, const DirectX::XMFLOAT3& aCamera);
	void updateMatrix();

	// スプライト
	void updateSprite(
		const DirectX::XMFLOAT3X3& aTransform,
		const DirectX::XMFLOAT2& aAnchor,
		const DirectX::XMFLOAT2& aPivot,
		const DirectX::XMINT2 aSplit
	);

	// その他
	void updateCamera(const DirectX::XMVECTOR& aPos, const DirectX::XMVECTOR& aRot);
	void updateDLight(const DirectX::XMVECTOR& aRot, const DirectX::XMFLOAT4& aCol);
	void updateColor(const DirectX::XMFLOAT4& aCol0, const DirectX::XMFLOAT4& aCol1);
	void updateMaterial(const OBJMaterial& aMaterial);

private:
	struct CB_DATA
	{
		CB_MATRIX MATRIX;
		CB_SPRITE SPRITE;
		CB_CAMERA CAMERA;
		CB_DLIGHT DLIGHT;
		CB_COLOR COLOR;
		CB_MATERIAL MATERIAL;
	};
	enum BufferList
	{
		MATRIX,
		SPRITE,
		CAMERA,
		DLIGHT,
		COLOR,
		MATERIAL,
	};
	std::unordered_map<int, ID3D11Buffer*> mBuffer;
	CB_DATA mData;
	DirectX::XMMATRIX mProj2D;

};

} // namespace
// EOF
