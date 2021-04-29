#pragma once

//-------------------------------------------------------------------------------------------------
namespace DX11 {

class IGameObjectInitialize
{
public:
	IGameObjectInitialize() = default;
	virtual ~IGameObjectInitialize() = default;
	virtual void initialize() = 0;

};

} // namespace
// EOF
