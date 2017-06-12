#include "Room.h"
#include <algorithm>

IMPLEMENT_SERIAL(CPlate, CObject, 1);
IMPLEMENT_SERIAL(CBasket, CObject, 1);
IMPLEMENT_SERIAL(CRoom, CObject, 1);

coord::coord(UINT r, UINT c) {
	row = r;
	col = c;
}
bool coord::operator == (const coord& c) {
	return (row == c.row) && (col == c.col);
}
// plate class realization
CPlate::CPlate(){
	position.col = 0;
	position.row = 0;
	num_fish = 0;
}
CPlate::CPlate(coord p, UINT nf) {
	position = p;
	num_fish = nf;
}

CPlate::CPlate(const CPlate& plate) {
	position = plate.position;
	num_fish = plate.num_fish;
}
CPlate& CPlate::operator = (const CPlate& plate) {
	position = plate.position;
	num_fish = plate.num_fish;
	return *this;
}
void CPlate::Serialize(CArchive& ar) {
	if (ar.IsStoring()){
		ar << position.col << position.row << num_fish;
	}
	else{
		ar >> position.col >> position.row >> num_fish;
	}
}

// basket class realization
CBasket::CBasket() {
	position.col = 0;
	position.row = 0;
}
CBasket::CBasket(coord p){
	position = p;
}
CBasket::CBasket(const CBasket& basket) {
	position = basket.position;
}
CBasket& CBasket::operator = (const CBasket& basket) {
	position = basket.position;
	return *this;
}
void CBasket::Serialize(CArchive& ar){
	if (ar.IsStoring()){
		ar << position.col << position.row;
	}
	else{
		ar >> position.col >> position.row;
	}
}

// room class realization
CRoom::CRoom()
{
	width = 20;
	height = 20;
	_plates = new plates_type;
	_cats = new cats_type;
	_baskets = new baskets_type;
}

CRoom::CRoom(size_t w, size_t h)
{
	_plates = new plates_type;
	_cats = new cats_type;
	_baskets = new baskets_type;

	width = w;
	height = h;
}

plates_type * CRoom::plates() const {
	return _plates;
}
cats_type * CRoom::cats() const {
	return _cats;
}
baskets_type * CRoom::baskets() const {
	return _baskets;
}

CRoom& CRoom::operator = (const CRoom& room) {
	width = room.width;
	height = room.height;
	// TODO: memory leak?!
	this->_plates->clear();
	this->_baskets->clear();
	std::copy(room._plates->begin(), room._plates->end(), std::back_inserter(*_plates));
	std::copy(room._baskets->begin(), room._baskets->end(), std::back_inserter(*_baskets));
	// std::copy(r._cats.begin(), r._cats.end(), std::back_inserter(_cats));
	return *this;
}

void CRoom::Serialize(CArchive& ar) {
	if (ar.IsStoring()) {
		ar << this->width << this->height;
		// plates
		ar << _plates->size();
		for (plates_iterator plate = _plates->begin(); plate != _plates->end(); ++plate) {
			(*plate)->Serialize(ar);
		}

		// baskets
		ar << _baskets->size();
		for (baskets_iterator basket = _baskets->begin(); basket != _baskets->end(); ++basket) {
			(*basket)->Serialize(ar);
		}
	}
	else {
		ar >> this->width >> this->height;
		//plates
		size_t nr_plates;
		ar >> nr_plates;
		_plates->resize(nr_plates);
		for (plates_iterator plate = _plates->begin(); plate != _plates->end(); ++plate) {
			(*plate)->Serialize(ar);
		}

		//baskets
		size_t nr_baskets;
		ar >> nr_baskets;
		_baskets->resize(nr_baskets);
		for (baskets_iterator basket = _baskets->begin(); basket != _baskets->end(); ++basket) {
			(*basket)->Serialize(ar);
		}
	}
}

CRoom::~CRoom() {
	delete _plates;
	delete _cats;
	delete _baskets;
}

UINT CRoom::at(UINT col, UINT row) {
	coord tmp;
	tmp.col = col;
	tmp.row = row;
	// plates
	for (plates_iterator plate = _plates->begin(); plate != _plates->end(); ++plate) {
		if ((*plate)->position == tmp) {
			if ((*plate)->num_fish > 0) {
				return FISH;
			}
			else {
				return PLATE;
			}
		}
	}

	// baskets
	for (baskets_iterator basket = _baskets->begin(); basket != _baskets->end(); ++basket) {
		if ((*basket)->position == tmp) {
			return BASKET;
		}
	}
	
	// nothing
	return BG;
}

void CRoom::AddBasket(CBasket* basket) {
	_baskets->push_back(basket);
}

void CRoom::AddPlate(CPlate* plate) {
	_plates->push_back(plate);
}

void CRoom::AddCat(ICat* cat) {
	_cats->push_back(cat);
}

void CRoom::RemoveBasket(size_t index) {
	CBasket* basket = (*_baskets)[index];
	_baskets->erase(_baskets->begin() + index);
	delete basket;
}

void CRoom::RemovePlate(size_t index) {
	CPlate* plate = (*_plates)[index];
	_plates->erase(_plates->begin() + index);
	delete plate;
}