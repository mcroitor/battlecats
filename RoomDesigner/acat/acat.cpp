#include "acat.h"

/*
std::string name;		// pet's name
std::string author;		// pet's owner
size_t stomach_volume;	// stomach volume
size_t sleep_speed;		// stomach speed clearing
size_t eat_speed;		// stomach speed filling
size_t speed;			// speed, just speed
*/
const CatConfig config = {
	"Vas'ka",
	"Krey",
	20,
	10,
	10,
	10
};

ACat::ACat(const CatConfig& cfg, CRoom* room): ICat(cfg, room) {

}

/*
  a simple example of Next method realization
*/
IAction* ACat::Next(IAction* action) {
	// does not exist any action
	if (action == nullptr) {
		if (this->stomachIsFull()) {
			return new GoToSleepAction(this, this->_room->beds());
		}
	}
	return nullptr;
}

ICat* createCat(CRoom* room) {
	return new ACat(::config, room);
}