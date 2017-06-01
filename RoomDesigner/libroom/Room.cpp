#include "Room.h"

IMPLEMENT_SERIAL(CPlate, CObject, 1);
IMPLEMENT_SERIAL(CBasket, CObject, 1);
IMPLEMENT_SERIAL(CRoom, CObject, 1);

coord::coord(UINT r, UINT c){
	row = r;
	col = c;
}
bool coord::operator == (const coord& c){
	return (row == c.row) && (col == c.col);
}
// plate class realization
CPlate::CPlate(){
	position.col = 0;
	position.row = 0;
	num_fish = 0;
}
CPlate::CPlate(coord p, UINT nf){
	position = p;
	num_fish = nf;
}
CPlate& CPlate::operator = (const CPlate& p){
	position = p.position;
	num_fish = p.num_fish;
	return *this;
}
void CPlate::Serialize(CArchive& ar){
	if (ar.IsStoring()){
		ar << position.col << position.row << num_fish;
	}
	else{
		ar >> position.col >> position.row >> num_fish;
	}
}

// basket class realization
CBasket::CBasket(){
	position.col = 0;
	position.row = 0;
}
CBasket::CBasket(coord p){
	position = p;
}
CBasket& CBasket::operator = (const CBasket& b){
	position = b.position;
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
}

CRoom::CRoom(size_t w, size_t h)
{
	width = w;
	height = h;
}

plates_type CRoom::plates() const {
	plates_type tmp;
	for (size_t i = 0; i != _plates.GetSize(); ++i) {
		tmp.push_back(_plates[i]);
	}
	return tmp;
}
cats_type CRoom::cats() const {
	cats_type tmp;
	for (size_t i = 0; i != _cats.GetSize(); ++i) {
		tmp.push_back(_cats[i]);
	}
	return tmp;
}
baskets_type CRoom::baskets() const {

}

CRoom& CRoom::operator = (const CRoom& r){
	width = r.width;
	height = r.height;
	this->_plates.RemoveAll();
	this->_sleeps.RemoveAll();
	this->_plates.Copy(r._plates);
	this->_sleeps.Copy(r._sleeps);
	return *this;
}

void CRoom::Serialize(CArchive& ar){
	if (ar.IsStoring()){
		ar << this->width << this->height;
	}
	else{
		ar >> this->width >> this->height;
	}
	_plates.Serialize(ar);
	_sleeps.Serialize(ar);
}

CRoom::~CRoom()
{
}

UINT CRoom::at(UINT col, UINT row){
	UINT i;
	coord tmp;
	tmp.col = col;
	tmp.row = row;
	// plates
	for (i = 0; i != _plates.GetSize(); ++i){
		if (_plates[i].position == tmp){
			if (_plates[i].num_fish > 0){
				return FISH;
			}
			else{
				return PLATE;
			}
		}
	}
	// baskets
	for (i = 0; i != _sleeps.GetSize(); ++i){
		if (_sleeps[i].position == tmp){
			return BASKET;
		}
	}
	// nothing
	return BG;
}