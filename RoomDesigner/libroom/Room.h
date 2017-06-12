#pragma once
#include "afx.h"
#include "iroom.h"
#include <afxwin.h> 

#ifndef ICAT_EXPORTS
#define ICAT_API __declspec(dllexport)
#endif

enum {
	BG,
	PLATE,
	FISH,
	BASKET
};

struct ICAT_API coord {
	UINT col, row;
	coord() = default;
	coord(UINT, UINT);
	bool operator == (const coord&);
};

struct ICAT_API Object : public CObject {
	coord position;

	Object() = default;
	virtual ~Object() {}
};

class ICAT_API CPlate : public Object {
public:
	UINT num_fish;

	DECLARE_SERIAL(CPlate);

	CPlate();
	CPlate(const CPlate&);
	CPlate(coord, UINT);

	CPlate& operator = (const CPlate&);
	void Serialize(CArchive&);
};

class ICAT_API CBasket : public Object {
public:
	DECLARE_SERIAL(CBasket);

	CBasket();
	CBasket(const CBasket&);
	CBasket(coord);

	CBasket& operator = (const CBasket&);
	void Serialize(CArchive&);
};

class ICAT_API CRoom : public CObject, IRoom {
	plates_type * _plates;
	baskets_type * _baskets;
	cats_type * _cats;
public:
	size_t width, height;

	DECLARE_SERIAL(CRoom);
	virtual plates_type * plates() const;
	virtual cats_type * cats() const;
	virtual baskets_type * baskets() const;
	void AddBasket(CBasket*);
	void AddPlate(CPlate*);
	void AddCat(ICat*);
	void RemoveBasket(size_t);
	void RemovePlate(size_t);

	CRoom();
	CRoom(size_t, size_t);
	CRoom& operator = (const CRoom&);
	UINT at(UINT, UINT);
	void Serialize(CArchive &);
	~CRoom();
};

