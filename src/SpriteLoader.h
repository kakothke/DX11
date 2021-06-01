#pragma once

//-------------------------------------------------------------------------------------------------
#include <d3d11.h>
#include <vector>
#include <unordered_map>
#include "Singleton.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// ���_�f�[�^�\����
struct SpriteVertex
{
	float pos[3];
	float uv[2];

	SpriteVertex()
		: pos{ 0,0,0 }
		, uv{ 0,0 }
	{
	}
};

/// �X�v���C�g�f�[�^�\����
struct SpriteData
{
	/// ���_�o�b�t�@(Shader���M�p)
	ID3D11Buffer* vertexBuffer;
	/// �t�@�C����
	const char* fileName;

	/// �R���X�g���N�^
	SpriteData()
		: vertexBuffer(nullptr)
	{
	}
	/// �f�X�g���N�^
	~SpriteData()
	{
		if (vertexBuffer) {
			vertexBuffer->Release();
			vertexBuffer = nullptr;
		}
	}
};

/// �X�v���C�g�ǂݍ��݃N���X
class SpriteLoader : public Singleton<SpriteLoader>
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	SpriteLoader();
	~SpriteLoader();
	//@}

	/// @name �ǂݍ��݁A�j��
	//@{
	bool load(const char* const aFileName);
	void release(const char* const aFileName);
	//@}

	/// @name OBJ�f�[�^���擾����
	//@{
	SpriteData* getSpriteData(const char* const aFileName);
	//@}

private:
	/// ���_�o�b�t�@���쐬����
	bool createVertexBuffer(const char* const aFileName);
	/// ���b�V�����쐬����
	void createMesh(SpriteVertex* aVertexes);
	/// ���b�V���̑傫�����e�N�X�`���[�̃T�C�Y�ɍ��킹��
	//void resizeMesh();

	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	/// �X�v���C�g�f�[�^
	std::unordered_map<const char*, SpriteData> mSpriteData;
	//@}

};

} // namespace
// EOF
