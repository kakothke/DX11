#pragma once

//-------------------------------------------------------------------------------------------------
#include <D3D11.h>
#include <unordered_map>
#include "Singleton.h"
#include "Vector3.h"
#include "ObjList.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// 頂点バッファ保存用構造体
struct ObjVertexData
{
	/// 頂点座標
	double position[3];
	/// UV座標
	double texture[2];
	/// 法線座標
	double normal[3];
};

/// objファイルデータ保存用構造体
struct ObjData
{
	/// 頂点バッファ(Shader送信用)
	ID3D11Buffer* vertexBuffer;
	/// インデックスバッファ(Shader送信用)
	ID3D11Buffer* indexBuffer;
	/// 入力レイアウト
	ID3D11InputLayout* inputLayout;
	/// 頂点バッファ保存用構造体コンテナ
	std::vector<ObjVertexData> vertexContainer;
	/// インデックスバッファコンテナ
	std::vector<UINT> indexContainer;

	/// コンストラクタ
	ObjData()
		: vertexBuffer(nullptr)
		, indexBuffer(nullptr)
		, inputLayout(nullptr)
		, vertexContainer()
		, indexContainer()
	{
		vertexContainer.clear();
		indexContainer.clear();
	}
	/// デストラクタ
	~ObjData()
	{
		if (vertexBuffer) {
			vertexBuffer->Release();
			vertexBuffer = nullptr;
		}
		if (indexBuffer) {
			indexBuffer->Release();
			indexBuffer = nullptr;
		}
		if (inputLayout) {
			inputLayout->Release();
			inputLayout = nullptr;
		}
		if (!vertexContainer.empty()) {
			vertexContainer.clear();
		}
		if (!indexContainer.empty()) {
			indexContainer.clear();
		}
	}
};

/// objファイル読み込みクラス
class ObjLoader : public Singleton<ObjLoader>
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	ObjLoader();
	~ObjLoader();
	//@}

	/// @name 読み込み、破棄
	//@{
	bool load(ObjList aObjList);
	void release(ObjList aObjList);
	//@}

	/// @name 読み込んだobjデータを返す
	//@{
	const ObjData& objData(ObjList aObjList);
	//@}

private:
	/// @name 内部実装関数
	//@{
	/// メッシュを作成する
	bool createMesh(ObjList aObjList);
	/// 頂点バッファを作成する
	bool createVertexBuffer(ObjList aObjList);
	/// インデックスバッファを作成する
	bool createIndexBuffer(ObjList aObjList);
	/// 文字列をfloat型に変換して座標情報をpushする
	template <typename T>
	void pushAtofVector(std::vector<std::vector<T>>& aData, const std::vector<std::string>& aStr);
	//@}

	/// @name プライベートメンバ変数
	//@{
	/// objファイルデータ
	std::unordered_map<ObjList, ObjData> mObjData;
	//@}

};

} // namespace
// EOF
