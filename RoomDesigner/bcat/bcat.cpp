#include "bcat.h"
#include <algorithm>

const CatConfig config = {
	"Valera",		// pet's name
	"JustQuality",	// pet's owner
	7,				// stomach volume
	5,				// stomach speed clearing
	6,				// stomach speed filling
	7				// speed, just speed
};

BCat::BCat(const CatConfig& cfg, IRoom* room) : ICat(cfg, room) {}

IAction* BCat::Next(IAction* action) {
	// does not exist any action
	if (action == nullptr) {
		if (this->stomachIsFull()) {
			// go to sleep
			return new GoToSleepAction(this);
		}
		else {
			plates_type plates = new std::deque<CPlate*>(this->getRoom()->plates()->begin(), this->getRoom()->plates()->end());
			std::sort(plates->begin(), plates->end(), by_distance(this));

			while (plates->size() > 0 && plates->front()->num_fish == 0) {
				plates->pop_front();
			}

			if (plates->size() == 0) {
				return new GoToSleepAction(this);
			}

			ComposedAction* composedAction = new ComposedAction(this);
			composedAction->push_back(new GoToAction(this, plates->front()));
			composedAction->push_back(new EatAction(this));

			return composedAction;
		}
	}
	return nullptr;
}

ICat* createCat(IRoom* room) {
	return new BCat(::config, room);
}