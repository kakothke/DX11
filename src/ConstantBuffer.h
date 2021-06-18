#pragma once

//-------------------------------------------------------------------------------------------------
#include <d3d11.h>
#include <DirectXMath.h>
#include <unordered_map>
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
	void setMatrixW(const DirectX::XMFLOAT3X3& aTransform);
	void setMatrixVP(const DirectX::XMFLOAT3X3& aTransform, const DirectX::XMFLOAT3& aCamera);
	void updateMatrix();
	/// スプライト
	void updateSprite(
		const DirectX::XMFLOAT3X3& aTransform,
		const DirectX::XMFLOAT2& aAnchor,
		const DirectX::XMFLOAT2& aPivot,
		const DirectX::XMINT2 aSplit
	);
	/// カメラ
	void updateCamera(const DirectX::XMVECTOR& aPos, const DirectX::XMVECTOR& aRot);
	/// ディレクショナルライト
	void updateDLight(const DirectX::XMVECTOR& aRot, const DirectX::XMFLOAT4& aCol);
	/// カラー
	void updateColor(const DirectX::XMFLOAT4& aCol0, const DirectX::XMFLOAT4& aCol1);
	/// OBJマテリアル
	void updateMaterial(const OBJMaterial& aMaterial);
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
