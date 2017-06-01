#pragma once
#include "afx.h"
#include "iroom.h"
#include <afxwin.h> 

class ICat;

enum {
	BG,
	PLATE,
	FISH,
	BASKET
};

struct __declspec(dllexport) coord{
	UINT col, row;
	coord() = default;
	coord(UINT, UINT);
	bool operator == (const coord&);
};

class __declspec(dllexport) CPlate : public CObject{
public:
	UINT num_fish;
	coord position;

	DECLARE_SERIAL(CPlate);

	CPlate();
	CPlate(coord, UINT);

	CPlate& operator = (const CPlate&);
	void Serialize(CArchive&);
};

class __declspec(dllexport) CBasket : public CObject{
public:
	coord position;

	DECLARE_SERIAL(CBasket);

	CBasket();
	CBasket(coord);

	CBasket& operator = (const CBasket&);
	void Serialize(CArchive&);
};

class __declspec(dllexport) CRoom :
	public CObject, IRoom
{
	CArray<CPlate> _plates;
	CArray<CBasket> _sleeps;
	CArray<ICat*> _cats;
public:
	size_t width, height;

	DECLARE_SERIAL(CRoom);
	virtual plates_type plates() const;
	virtual cats_type cats() const;
	virtual baskets_type baskets() const;
	CRoom();
	CRoom(size_t, size_t);
	CRoom& operator = (const CRoom&);
	UINT at(UINT, UINT);
	void Serialize(CArchive &);
	~CRoom();
};

