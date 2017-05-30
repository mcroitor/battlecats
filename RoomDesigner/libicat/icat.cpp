#include "icat.h"
#include <algorithm>

distance_type distance(coord p1, coord p2){
	return sqrt((p1.x - p2.x)*(p1.x - p2.x) +
		(p1.x - p2.x)*(p1.x - p2.x));
}

distance_type distance(Object* p1, Object* p2){
	return distance(p1->position(), p2->position());
}

//////////////////////////////////////////
IAction::IAction(ICat* cat) : _cat(cat) {}

const CatConfig IAction::catConfig() const { return _cat->getConfig(); }


// move action
MoveAction::MoveAction(ICat* cat, distance_type t) : IAction(cat) {
	_distance = t;
}

ACTION_T MoveAction::type() const {
	return ACTION_T::MOVE;
}
distance_type MoveAction::distance() const {
	return _distance;
}
void MoveAction::move(){
	_distance = (_distance > catConfig().speed) ? _distance - catConfig().speed : 0;
}

// // TODO 01: may be later
//RotateAction::RotateAction(ICat* cat, angle_type angle) : IAction(cat) {
//	_angle = angle;
//}
//ACTION_T RotateAction::type() const {
//	return ACTION_T::ROTATE;
//}
//angle_type RotateAction::angle() const {
//	return _angle;
//}
//void RotateAction::rotate(){
//	_angle = (_angle > catConfig().rotation_speed) ? _angle - catConfig().rotation_speed : 0;
//}
// eat_action
EatAction::EatAction(ICat* cat) : IAction(cat){
}
ACTION_T EatAction::type() const  {
	return ACTION_T::EAT;
}

// sleep action
ACTION_T SleepAction::type() const  {
	return ACTION_T::SLEEP;
}

// composed action
ACTION_T ComposedAction::type() const {
	return ACTION_T::COMPOSED;
}
const actions_type& ComposedAction::actions() const {
	return _actions;
}
void ComposedAction::push_back(IAction* ac){
	_actions.push_back(ac);
}


// go to point action
GoToAction::GoToAction(ICat* cat, const Object* obj) : ComposedAction(cat){
	// rotate
	// TODO 01: may be later
	//angle_type angle = cat->angle(obj->position());
	//this->push_back(new RotateAction(cat, angle));
	// move to
	distance_type dist = ::distance(cat->position(), obj->position());
	this->push_back(new MoveAction(cat, dist));
}
// go home action
GoHomeAction::GoHomeAction(ICat* cat, const beds_type& p) : ComposedAction(cat){
	// detect nearest bed
	CBasket* bed = *std::min_element(p.begin(), p.end(), by_distance(cat));
	// rotate
	// TODO 01: may be later
//	angle_type angle = cat->angle(bed->position());
//	this->push_back(new RotateAction(cat, angle));
	// move to
	GoToAction(cat, bed);
	// sleep
	size_t count = cat->fishInStomach() / cat->getConfig().sleep_speed + 
		(cat->fishInStomach() % cat->getConfig().sleep_speed != 0) ? 1 : 0;
	while (count--){
		this->push_back(new SleepAction(cat));
	}
}
//////////////////////////////////////////
ICat::ICat(const CatConfig& cfg, IRoom* room){
	_cfg = cfg;
	_room = room;
}
ICat::~ICat(){};

const size_t ICat::fishInStomach() const {
	return _eated_fishes;
}
const size_t ICat::stomachIsFull() const {
	return _eated_fishes == _cfg.stomach_volume;
}

const distance_type ICat::distance(coord p) const {
	return (distance_type)::distance(position(), p);
}
//const angle_type ICat::angle(coord p) const {
//	size_t x = _position.x - p.x;
//	size_t y = _position.y - p.y;
//	distance_type dist = distance(p);
//
//	double cos_gamma = (x * cos(_angle) + y * sin(_angle)) / (dist * dist);
//
//	return acos(cos_gamma);
//}
CatConfig ICat::getConfig() const {
	return _cfg;
}

// order functors
// by distance
by_distance::by_distance(ICat* p){
	cat = p;
}
bool by_distance::operator()(Object* p1, Object* p2) const{
	return distance(cat->position(), p1->position()) <
		distance(cat->position(), p2->position());
}

// by volume
by_volume::by_volume(ICat* p){ cat = p; }

bool by_volume::operator()(CPlate* p1, CPlate* p2) const{
	return p1->nr_fishes < p2->nr_fishes;
}

// by angle
//by_angle::by_angle(ICat* p){
//	cat = p;
//}

//bool by_angle::operator()(Object* p1, Object* p2) const{
//	return cat->angle(p1->position) < cat->angle(p2->position);
//}