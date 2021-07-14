#pragma once

//-------------------------------------------------------------------------------------------------
#include "Input.h"
#include "Singleton.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// �����̃f�o�C�X�̓��͏󋵂��܂Ƃ߂�񋓌^
enum class InputCode
{
	/// ����{�^��
	OK,
	/// �L�����Z���{�^��
	Cancel,
	/// ��
	UP,
	/// ��
	DOWN,

	TERM,
};

/// �����̃f�o�C�X�̓��͏󋵂��Ǘ�����
class InputManager : public Singleton<InputManager>
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	InputManager();
	~InputManager();
	//@}
	
	/// @name �X�V
	//@{
	void update();
	//@}

	/// @name ���͏󋵎擾
	//@{
	/// �������͏󋵂�Ԃ�(-1.0f~1.0f)
	const Vector2& axes() const;
	/// �������͏󋵂�Ԃ�(-1~1)
	const Vector2& axesRaw() const;
	/// �{�^���������Ă��邩
	bool getButton(const InputCode& aCode) const;
	/// �{�^������������
	bool getButtonDown(const InputCode& aCode) const;
	/// �{�^���𗣂�����
	bool getButtonUp(const InputCode& aCode) const;
	//@}

private:
	/// @name ��������
	//@{
	/// �������͏󋵍X�V
	void updateAxes();
	/// �{�^�����͏󋵍X�V
	void updateButtons();
	//@}

	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	/// ����(-1.0f~1.0f)
	Vector2 mAxes;
	/// ����(-1~1)
	Vector2 mAxesRaw;
	/// ���݂̓��͏�
	bool mState[(int)InputCode::TERM];
	/// �O�t���[���̓��͏�
	bool mPrevState[(int)InputCode::TERM];
	//@}

};

} // namespace
// EOF
