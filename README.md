# battlecats
Is a simulator for testing (or gaming?!) exploring algorithms.

Idea is taken from GalaxyFX contest (http://ru.jfx.wikia.com/wiki/GalaxyFX).

Try to create own Battle Cat!

## Description (RUS)

Голодные котята захватили комнату!! И каждый из них, стимулируемый своим ЭГО, собирается съесть как можно больше рыбы... Кто окажется победителем в этой борьбе за еду?!

В комнате находятся тарелки с рыбой, корзинки для сна и котята в корзинках. Вам необходимо запрограммировать котенка таким образом, чтобы он ел рыбу, спал... Соревнование проводится между несколькими котятами, побеждает тот котенок, который съедает больше всего рыбы за определенный промежуток времени

## создание проекта
шаблон проекта (а также простейший пример) представлен в проекте *acat*.

Пример заголовочного файла *acat.h*:
```C++
#ifndef MY_KITTEN
#define MY_KITTEN

#include ".\libicat\icat.h"

class ACat: public ICat {
public:
	ACat(const CatConfig& /*cfg*/, IRoom* /*room*/);
	virtual IAction* Next(IAction* /*action*/) final;
};

/*
 * this is a interface function of dll,  creates a cat
 */
extern "C" __declspec(dllexport) ICat* createCat(IRoom* /*room*/);
#endif
```
Пример реализации котенка (*acat.cpp*)
```C++
#include "acat.h"
#include <algorithm>

const CatConfig config = {
	"Vas'ka",   // pet's name
	"Krey",     // pet's owner
	20,         // stomach volume
	10,         // stomach speed clearing
	10,         // stomach speed filling
	10          // speed, just speed
};

ACat::ACat(const CatConfig& cfg, IRoom* room): ICat(cfg, room) {}

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
```
## описание доступных методов / переменных
### Cat Config
```C++
struct CatConfig {
	std::string name;		// pet's name
	std::string author;		// pet's owner
	size_t stomach_volume;		// stomache volume
	size_t sleep_speed;		// stomach speed clearing
	size_t eat_speed;		// stomach speed filling
	size_t speed;			// kitten's speed
};
```
### Cat
```C++
class ICat : public Object {
	virtual const size_t fishInStomach() const final;
	virtual const size_t stomachIsFull() const final;
	virtual const distance_type distance(coord /*p*/) const final;
	virtual CatConfig getConfig() const final;
	virtual const IRoom* getRoom() const final;
	virtual IAction* Next(IAction* /*action*/) = 0;
};
```
### Room
```C++
struct IRoom {
	virtual plates_type plates() const = 0;
	virtual cats_type cats() const = 0;
	virtual baskets_type baskets() const = 0;
};
```
### Actions
основная идея построения алгоритма поведения котенка - выбор действия(списка действий), в зависимости от текущего его состояния. Если котенок голоден - идти к наиболее перспективной, с его точки зрения, тарелке. Если желудок полон - идти спать, пока еда не переварится.

Каждое событие должно принимать в качестве параметра указатель на котенка.
* _MoveAction_ - атомарное действие, движение котенка к нужному объекту за единицу времени. Перемещает на _speed_ единиц в сторону объекта
* _EatAction_ - атомарное действие, поедание рыбы котенком за единицу времени. Наполняет желудок котенка на _eat_speed_ единиц
* _SleepAction_ - атомарное действие, сон за единицу времени. Уменьшает количество съеденой рыбы на sleep_speed единиц
* _ComposedAction_ - базовое составное действие. В него можно помещать любые действия в конец списка, при помощи команды _push_back_.
* _GoToAction_ - составное действие, содержит список_ MoveAction_, необходимых для достижения объекта.
* _GoToSleepAction_ - составное действие, отправляет котёнка к ближайшей корзинке и "укладывает его спать"

