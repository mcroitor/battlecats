#pragma once

#include "..\libicat\icat.h"

class ACat: public ICat {
public:
	ACat(const CatConfig& /*cfg*/, IRoom* /*room*/);
	virtual IAction* Next(IAction* /*action*/) final;
};

/*
 * this is a interface function of dll,  creates a cat
 */
extern "C" __declspec(dllexport) ICat* createCat(IRoom* /*room*/);