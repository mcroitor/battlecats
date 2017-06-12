#pragma once

#include "..\libicat\icat.h"

class BCat : public ICat {
public:
	BCat(const CatConfig& /*cfg*/, IRoom* /*room*/);
	virtual IAction* Next(IAction* /*action*/) final;
};

extern "C" __declspec(dllexport) ICat* createCat(IRoom* /*room*/);