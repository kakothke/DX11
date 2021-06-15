#pragma once

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// �V���O���g��
template <class T>
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
