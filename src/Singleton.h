#pragma once

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// �V���O���g��
template <typename T>
class Singleton
{
public:
	static T* getInst() {
		static T inst;
		return &inst;
	};

protected:
	Singleton() = default;
	virtual ~Singleton() = default;
	Singleton(const Singleton & r) = default;
	Singleton& operator=(const Singleton & r) = default;

};

} // namespace
// EOF
