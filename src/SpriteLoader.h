#pragma once

//-------------------------------------------------------------------------------------------------
#include <d3d11.h>
#include <DirectXMath.h>
#include <vector>
#include <unordered_map>
#include "Singleton.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

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
	bool load(const LPCSTR aFileName);
	void release(const LPCSTR aFileName);
	//@}

	/// @name ���J�\����
	//@{
	/// ���_�f�[�^�\����
	struct SpriteVertex
	{
		float pos[3] = {};
		float uv[2] = {};
	};
	/// �X�v���C�g�f�[�^�\����
	struct SpriteData
	{
		/// ���_�o�b�t�@(Shader���M�p)
		ID3D11Buffer* vertexBuffer;
		/// �t�@�C����
		LPCSTR fileName;
		/// �f�X�g���N�^
		~SpriteData();
	};
	//@}

	/// @name �A�N�Z�T
	//@{
	/// �X�v���C�g�f�[�^���擾����
	SpriteData* getSpriteData(const LPCSTR aFileName);
	//@}

private:
	/// @name ��������
	//@{
	/// ���_�o�b�t�@���쐬����
	bool createVertexBuffer(const LPCSTR aFileName);
	/// ���b�V�����쐬����
	void createMesh(const LPCSTR aFileName, SpriteVertex* aVertexes);
	//@}

	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	/// �X�v���C�g�f�[�^
	std::unordered_map<LPCSTR, SpriteData> mSpriteData;
	//@}

};

} // namespace
// EOF
