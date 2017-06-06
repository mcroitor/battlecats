#include "icat.h"
#include <algorithm>

// helper methods
distance_type distance(coord p1, coord p2) {
	return sqrt((p1.row - p2.row)*(p1.row - p2.row) +
		(p1.col - p2.col)*(p1.col - p2.col));
}
distance_type distance(Object* object1, Object* object2) {
	return distance(object1->position, object2->position);
}

// cat configuration
const CatConfig IAction::catConfig() const { return _cat->getConfig(); }

// action constructors
IAction::IAction(ICat* cat) : _cat(cat) {}
MoveAction::MoveAction(ICat* cat, distance_type dist) : IAction(cat) { _distance = dist; }
EatAction::EatAction(ICat* cat) : IAction(cat) {}
SleepAction::SleepAction(ICat* cat) : IAction(cat) {}
ComposedAction::ComposedAction(ICat* cat) : IAction(cat) {}

// action types
ACTION_T MoveAction::type()		const { return ACTION_T::MOVE; }
ACTION_T EatAction::type()		const { return ACTION_T::EAT; }
ACTION_T SleepAction::type()	const { return ACTION_T::SLEEP; }
ACTION_T ComposedAction::type() const { return ACTION_T::COMPOSED; }

distance_type MoveAction::distance() const {
	return _distance;
}
void MoveAction::move(){
	_distance = (_distance > catConfig().speed) ? _distance - catConfig().speed : 0;
}

void SleepAction::sleep() const{ /* TODO */ }

const actions_type& ComposedAction::actions() const {
	return _actions;
}
void ComposedAction::push_back(IAction* action) {
	_actions.push_back(action);
}

GoToAction::GoToAction(ICat* cat, const Object* object) : ComposedAction(cat) {
	// move to
	distance_type dist = ::distance(cat->position, object->position);
	this->push_back(new MoveAction(cat, dist));
}

GoToSleepAction::GoToSleepAction(ICat* cat) : ComposedAction(cat) {
	// detect nearest bed
	CBasket* bed = *std::min_element(cat->getRoom()->baskets().begin(), cat->getRoom()->baskets().end(), by_distance(cat));
	// move to
	GoToAction(cat, bed);
	// sleep
	size_t sleep_speed = cat->getConfig().sleep_speed;
	size_t fishInStomach = cat->fishInStomach();
	size_t fishLeft = fishInStomach / sleep_speed + (fishInStomach % sleep_speed != 0) ? 1 : 0;

	while (fishLeft--) {
		this->push_back(new SleepAction(cat));
	}
}

CatConfig ICat::getConfig() const { return _cfg; }
const IRoom * ICat::getRoom() const
{
	return _room;
}
ICat::ICat(const CatConfig& cfg, IRoom* room) {
	_cfg = cfg;
	_room = room;
}
ICat::~ICat() {};
const size_t ICat::fishInStomach() const {
	return _eated_fishes;
}
const size_t ICat::stomachIsFull() const {
	return _eated_fishes == _cfg.stomach_volume;
}
const distance_type ICat::distance(coord p) const {
	return (distance_type)::distance(position, p);
}

// order functors
by_distance::by_distance(ICat* cat) { _cat = cat; }
by_volume::by_volume(ICat* cat) { _cat = cat; }

bool by_distance::operator()(Object* object1, Object* object2) const {
	return distance(_cat->position, object1->position) <
		distance(_cat->position, object2->position);
}
bool by_volume::operator()(CPlate* plate1, CPlate* plate2) const {
	return plate1->num_fish < plate2->num_fish;
}