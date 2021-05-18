#pragma once

//-------------------------------------------------------------------------------------------------
#include <D3D11.h>
#include <unordered_map>
#include "Singleton.h"
#include "Vector3.h"
#include "OBJList.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// ���_�f�[�^�\����
struct OBJVertexData
{
	/// ���_���W
	float pos[3];
	/// UV���W
	float uv[2];
	/// �@�����W
	float nor[3];
};

/// OBJ�t�@�C���f�[�^�ۑ��p�\����
struct OBJData
{
	/// ���_�o�b�t�@(Shader���M�p)
	ID3D11Buffer* vertexBuffer;
	/// �C���f�b�N�X�o�b�t�@(Shader���M�p)
	ID3D11Buffer* indexBuffer;
	/// �C���f�b�N�X�o�b�t�@�R���e�i
	std::vector<UWORD> indexes;

	/// �R���X�g���N�^
	OBJData()
		: vertexBuffer(nullptr)
		, indexBuffer(nullptr)
		, indexes()
	{
		indexes.clear();
	}
	/// �f�X�g���N�^
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

/// OBJ�t�@�C���ǂݍ��݃N���X
class OBJLoader : public Singleton<OBJLoader>
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	OBJLoader();
	~OBJLoader();
	//@}

	/// @name �ǂݍ��݁A�j��
	//@{
	bool load(const OBJList& aOBJList);
	void release(const OBJList& aOBJList);
	//@}

	/// @name OBJ�f�[�^���擾����
	//@{
	OBJData* getObjData(OBJList aOBJList);
	//@}

private:
	/// @name ���������֐�
	//@{
	/// ���b�V�����쐬����
	bool createMesh(const OBJList& aOBJList, std::vector<OBJVertexData>& aVertexData);
	/// ���_�o�b�t�@���쐬����
	bool createVertexBuffer(const OBJList& aOBJList, const std::vector<OBJVertexData>& aVertexData);
	/// �C���f�b�N�X�o�b�t�@���쐬����
	bool createIndexBuffer(const OBJList& aOBJList);
	/// �������float�^�ɕϊ����č��W����push����
	template <typename T>
	void pushAtofVector(std::vector<std::vector<T>>& aData, const std::vector<std::string>& aStr);
	//@}

	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	/// obj�t�@�C���f�[�^
	std::unordered_map<OBJList, OBJData> mOBJData;
	//@}

};

} // namespace
// EOF
