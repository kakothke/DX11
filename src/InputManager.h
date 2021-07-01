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
	const Vector2& getAxes() const;
	bool getInput(const InputCode& aCode) const;
	bool getInputDown(const InputCode& aCode) const;
	bool getInputUp(const InputCode& aCode) const;

	Vector2 getAxesRaw(float Speed);
	//@}

private:
	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	/// ����
	Vector2 mAxes;
	Vector2 mAxesRaw;
	/// ���݂̓��͏�
	bool mState[(int)InputCode::TERM];
	/// �O�t���[���̓��͏�
	bool mPrevState[(int)InputCode::TERM];

	int Code;
	//@}

};

} // namespace
// EOF
