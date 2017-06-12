#ifndef ICAT_H
#define ICAT_H

#include <string>
#include <deque>
#include "..\libroom\Room.h"

#ifndef ICAT_API
#define ICAT_API __declspec(dllexport)
#endif

struct	coord;
struct	CatConfig;
class	ICat;
class	IAction;
class	CPlate;
class	CBasket;

typedef std::deque<IAction*>	actions_type;
typedef double					distance_type;


enum class ACTION_T {
	NO_ACTION = 0,
	MOVE = 1,
	EAT = 2,
	SLEEP = 3,
	COMPOSED = 10
};

struct CatConfig {
	std::string name;
	std::string author;
	size_t stomach_volume;
	size_t sleep_speed;		// stomach speed clearing
	size_t eat_speed;		// stomach speed filling
	size_t speed;
};

// an iterface for action
class IAction {
public:
	IAction(ICat* /*cat*/);
	virtual ACTION_T type() const = 0;
protected:
	virtual ICAT_API const CatConfig catConfig() const final;
	ICat* _cat;
};

// move action
struct ICAT_API MoveAction : public IAction {
	MoveAction(ICat* /*cat*/, distance_type /*type*/);
	virtual ACTION_T type() const override final;
	distance_type distance() const;
	void move();
protected:
	distance_type _distance;
};

struct ICAT_API EatAction : IAction {
	EatAction(ICat* /*cat*/);
	virtual ACTION_T type() const override final;
};

struct ICAT_API SleepAction : IAction {
	SleepAction(ICat* /*cat*/);
	virtual ACTION_T type() const override final;
	virtual void sleep() const final;
};

struct ICAT_API ComposedAction : IAction {
	ComposedAction(ICat* /*cat*/);
	virtual ACTION_T type() const override final;
	const actions_type& actions() const;
	void push_back(IAction* /*action*/);
protected:
	actions_type _actions;
};

struct ICAT_API GoToAction : public ComposedAction {
	GoToAction(ICat* /*cat*/, const Object* /*object*/);
};

struct ICAT_API GoToSleepAction : public ComposedAction {
	GoToSleepAction(ICat* /*cat*/);
};

/* An interface for Cat. */
class ICAT_API ICat : public Object {
protected:
	CatConfig	_cfg;
	size_t		_eated_fishes;
	IRoom*		_room;
public:
	ICat(const CatConfig& /*cfg*/, IRoom* /*room*/);
	virtual ~ICat();

	virtual const size_t fishInStomach() const final;
	virtual const size_t stomachIsFull() const final;
	virtual const distance_type distance(coord /*p*/) const final;
	virtual CatConfig getConfig() const final;
	virtual const IRoom* getRoom() const final;
	virtual IAction* Next(IAction* /*action*/) = 0;
};

/* functors for sorting */
struct ICAT_API by_distance {
	ICat* _cat;
	by_distance(ICat* /*cat*/);
	bool operator()(Object* /*object1*/, Object* /*object2*/) const;

};

struct ICAT_API by_volume {
	ICat* _cat;
	by_volume(ICat* /*cat*/);
	bool operator()(CPlate* /*plate1*/, CPlate* /*plate2*/) const;
};

#endif /* ICAT_H */