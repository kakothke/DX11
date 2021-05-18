#pragma once

//-------------------------------------------------------------------------------------------------
#include <D3D11.h>
#include <unordered_map>
#include "Singleton.h"
#include "Vector3.h"
#include "OBJList.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// 頂点データ構造体
struct OBJVertexData
{
	/// 頂点座標
	float pos[3];
	/// UV座標
	float uv[2];
	/// 法線座標
	float nor[3];
};

/// OBJファイルデータ保存用構造体
struct OBJData
{
	/// 頂点バッファ(Shader送信用)
	ID3D11Buffer* vertexBuffer;
	/// インデックスバッファ(Shader送信用)
	ID3D11Buffer* indexBuffer;
	/// インデックスバッファコンテナ
	std::vector<UWORD> indexes;

	/// コンストラクタ
	OBJData()
		: vertexBuffer(nullptr)
		, indexBuffer(nullptr)
		, indexes()
	{
		indexes.clear();
	}
	/// デストラクタ
	~OBJData()
	{
		if (vertexBuffer) {
			vertexBuffer->Release();
			vertexBuffer = nullptr;
		}
		if (indexBuffer) {
			indexBuffer->Release();
			indexBuffer = nullptr;
		}
		if (!indexes.empty()) {
			indexes.clear();
		}
	}
};

/// OBJファイル読み込みクラス
class OBJLoader : public Singleton<OBJLoader>
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	OBJLoader();
	~OBJLoader();
	//@}

	/// @name 読み込み、破棄
	//@{
	bool load(const OBJList& aOBJList);
	void release(const OBJList& aOBJList);
	//@}

	/// @name OBJデータを取得する
	//@{
	OBJData* getObjData(OBJList aOBJList);
	//@}

private:
	/// @name 内部実装関数
	//@{
	/// メッシュを作成する
	bool createMesh(const OBJList& aOBJList, std::vector<OBJVertexData>& aVertexData);
	/// 頂点バッファを作成する
	bool createVertexBuffer(const OBJList& aOBJList, const std::vector<OBJVertexData>& aVertexData);
	/// インデックスバッファを作成する
	bool createIndexBuffer(const OBJList& aOBJList);
	/// 文字列をfloat型に変換して座標情報をpushする
	template <typename T>
	void pushAtofVector(std::vector<std::vector<T>>& aData, const std::vector<std::string>& aStr);
	//@}

	/// @name プライベートメンバ変数
	//@{
	/// objファイルデータ
	std::unordered_map<OBJList, OBJData> mOBJData;
	//@}

};

} // namespace
// EOF
