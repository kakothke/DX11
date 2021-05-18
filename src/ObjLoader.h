#pragma once

//-------------------------------------------------------------------------------------------------
#include <D3D11.h>
#include <vector>
#include <fstream>
#include <string>
#include <unordered_map>
#include "Singleton.h"

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
	bool load(const char* aFileName);
	void release(const char* aFileName);
	//@}

	/// @name OBJデータを取得する
	//@{
	OBJData* getObjData(const char* aFileName);
	//@}

private:
	/// @name 内部実装関数
	//@{
	/// メッシュを作成する
	bool createMesh(const char* aFileName, std::vector<OBJVertexData>& aVertexData);
	/// 頂点バッファを作成する
	bool createVertexBuffer(const char* aFileName, const std::vector<OBJVertexData>& aVertexData);
	/// インデックスバッファを作成する
	bool createIndexBuffer(const char* aFileName);
	/// 文字列をfloat型に変換して座標情報をpushする
	template <typename T>
	void pushAtofVector(std::vector<std::vector<T>>& aData, const std::vector<std::string>& aStr);
	//@}

	/// @name プライベートメンバ変数
	//@{
	/// objファイルデータ
	std::unordered_map<const char*, OBJData> mOBJData;
	//@}

};

} // namespace
// EOF
