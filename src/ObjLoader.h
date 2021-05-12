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
	double position[3];
	/// UV���W
	double texture[2];
	/// �@�����W
	double normal[3];
};

/// obj�t�@�C���f�[�^�ۑ��p�\����
struct ObjData
{
	/// ���_�o�b�t�@(Shader���M�p)
	ID3D11Buffer* vertexBuffer;
	/// �C���f�b�N�X�o�b�t�@(Shader���M�p)
	ID3D11Buffer* indexBuffer;
	/// ���̓��C�A�E�g
	ID3D11InputLayout* inputLayout;
	/// ���_�o�b�t�@�ۑ��p�\���̃R���e�i
	std::vector<ObjVertexData> vertexContainer;
	/// �C���f�b�N�X�o�b�t�@�R���e�i
	std::vector<UINT> indexContainer;

	/// �R���X�g���N�^
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

/// obj�t�@�C���ǂݍ��݃N���X
class ObjLoader : public Singleton<ObjLoader>
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	ObjLoader();
	~ObjLoader();
	//@}

	/// @name �ǂݍ��݁A�j��
	//@{
	bool load(ObjList aObjList);
	void release(ObjList aObjList);
	//@}

	/// @name �ǂݍ���obj�f�[�^��Ԃ�
	//@{
	const ObjData& objData(ObjList aObjList);
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
	//@}

};

} // namespace
// EOF
