#pragma once
#include <deque>

class	CPlate;
class	CBasket;
class	ICat;

typedef std::deque<CPlate*>		plates_type;
typedef std::deque<ICat*>		cats_type;
typedef std::deque<CBasket*>	baskets_type;
typedef std::deque<CPlate*>::iterator	plates_iterator;
typedef std::deque<ICat*>::iterator		cats_iterator;
typedef std::deque<CBasket*>::iterator	baskets_iterator;

struct IRoom {
	virtual plates_type * plates() const = 0;
	virtual cats_type * cats() const = 0;
	virtual baskets_type * baskets() const = 0;
};