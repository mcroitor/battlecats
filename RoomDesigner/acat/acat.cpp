#include "acat.h"
#include <algorithm>

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

ACat::ACat(const CatConfig& cfg, IRoom* room): ICat(cfg, room) {

}

/*
  a simple example of Next method realization
*/
IAction* ACat::Next(IAction* action) {
	// does not exist any action
	if (action == nullptr) {
		if (this->stomachIsFull()) {
			// go to sleep
			return new GoToSleepAction(this);
		}
		else {
			// where is a plate with more fish?!
			plates_type plates(this->getRoom()->plates().begin(), this->getRoom()->plates().end());
			std::sort(plates.begin(), plates.end(), by_volume(this));
			ComposedAction* composedAction = new ComposedAction(this);
			// go to this plate
			composedAction->push_back(new GoToAction(this, plates.front()));
			// eat from plate
			composedAction->push_back(new EatAction(this));
			return composedAction;
		}
	}
	return nullptr;
}

ICat* createCat(IRoom* room) {
	return new ACat(::config, room);
}