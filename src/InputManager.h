#pragma once

//-------------------------------------------------------------------------------------------------
#include "Input.h"
#include "Singleton.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

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
	InputManager();
	~InputManager();
	
	void update();

	const Vector2& getAxes() const;
	bool getInput(const InputCode& aCode) const;
	bool getInputDown(const InputCode& aCode) const;
	bool getInputUp(const InputCode& aCode) const;

private:
	Vector2 mAxes;
	bool mState[(int)InputCode::TERM];
	bool mPrevState[(int)InputCode::TERM];

};

} // namespace
// EOF
