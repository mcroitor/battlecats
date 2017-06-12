#pragma once
#include "afx.h"

class ICat;

enum {
	BG,
	PLATE,
	FISH,
	BASKET
};

struct coord{
	UINT col, row;
	coord() = default;
	coord(UINT, UINT);
	bool operator == (const coord&);
};

struct CPlate: public CObject{
	UINT num_fish;
	coord position;

	DECLARE_SERIAL(CPlate);

	CPlate();
	CPlate(coord, UINT);

	CPlate& operator = (const CPlate&);
	void Serialize(CArchive&);
};

struct CBasket: public CObject{
	coord position;

	DECLARE_SERIAL(CBasket);

	CBasket();
	CBasket(coord);

	CBasket& operator = (const CBasket&);
	void Serialize(CArchive&);
};

class CRoom :
	public CObject
{
public:
	size_t width, height;
	CArray<CPlate> plates;
	CArray<CBasket> sleeps;
	CArray<ICat*> cats;
	DECLARE_SERIAL(CRoom);

	CRoom();
	CRoom(size_t, size_t);
	CRoom& operator = (const CRoom&);
	UINT at(UINT, UINT);
	void Serialize(CArchive &);
	~CRoom();
};

