#pragma once

//-------------------------------------------------------------------------------------------------
#include <D3D11.h>
#include <unordered_map>
#include "Singleton.h"
#include "Vector3.h"
#include "ObjList.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// ���_�o�b�t�@�ۑ��p�\����
struct ObjVertexData
{
	/// ���_���W
	float pos[3];
	/// UV���W
	float uv[2];
	/// �@�����W
	float nor[3];
};

/// obj�t�@�C���f�[�^�ۑ��p�\����
struct ObjData
{
	/// ���_�o�b�t�@(Shader���M�p)
	ID3D11Buffer* vertexBuffer;
	/// �C���f�b�N�X�o�b�t�@(Shader���M�p)
	ID3D11Buffer* indexBuffer;
	/// �C���f�b�N�X�o�b�t�@�R���e�i
	std::vector<UWORD> indexes;

	/// �R���X�g���N�^
	ObjData()
		: vertexBuffer(nullptr)
		, indexBuffer(nullptr)
		, indexes()
	{
		indexes.clear();
	}
	/// �f�X�g���N�^
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
		if (!indexes.empty()) {
			indexes.clear();
		}
	}
};

/// obj�t�@�C���ǂݍ��݃N���X
class ObjLoader : public Singleton<ObjLoader>
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	ObjLoader();
	~ObjLoader();
	//@}

	/// @name �쐬�A�j��
	//@{
	bool load(ObjList aObjList);
	void release(ObjList aObjList);
	//@}

	/// @name �ǂݍ���obj�f�[�^��Ԃ�
	//@{
	ObjData* getObjData(ObjList aObjList);
	//@}

private:
	/// @name ���������֐�
	//@{
	/// ���b�V�����쐬����
	bool createMesh(ObjList aObjList);
	/// ���_�o�b�t�@���쐬����
	bool createVertexBuffer(ObjList aObjList);
	/// �C���f�b�N�X�o�b�t�@���쐬����
	bool createIndexBuffer(ObjList aObjList);
	/// �������float�^�ɕϊ����č��W����push����
	template <typename T>
	void pushAtofVector(std::vector<std::vector<T>>& aData, const std::vector<std::string>& aStr);
	//@}

	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	/// obj�t�@�C���f�[�^
	std::unordered_map<ObjList, ObjData> mObjData;
	/// ���_�o�b�t�@�ۑ��p�\���̃R���e�i
	std::vector<ObjVertexData> mVertexData;
	//@}

};

} // namespace
// EOF
