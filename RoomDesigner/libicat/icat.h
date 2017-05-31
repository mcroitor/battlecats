#ifndef ICAT_H
#define ICAT_H

#include <string>
#include <vector>

class	ICat;
class	IAction;
struct	coord;
struct	CRoom;
struct	CPlate;
struct	CBasket;
struct	CatConfig;

typedef std::vector<IAction*>	actions_type;
typedef actions_type::iterator	actions_iterator;
typedef std::vector<CPlate*>	plates_type;
typedef plates_type::iterator	plates_iterator;
typedef std::vector<ICat*>		cats_type;
typedef cats_type::iterator		cats_iterator;
typedef std::vector<CBasket*>	beds_type;
typedef beds_type::iterator		beds_iterator;
typedef double					distance_type;

enum class ACTION_T {
	NO_ACTION = 0,
	MOVE = 1,
	EAT = 2,
	SLEEP = 3,
	COMPOSED = 10
};

struct coord {
	size_t x, y;
};

struct CRoom {};

struct Object {
	coord position;
};

struct CPlate : public Object {
	size_t nr_fishes;
};

struct CBasket : public Object {};

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
	virtual const CatConfig catConfig() const final;
	ICat* _cat;
};

// move action
struct MoveAction : public IAction {
	MoveAction(ICat* /*cat*/, distance_type /*type*/);
	virtual ACTION_T type() const override final;
	distance_type distance() const;
	void move();
protected:
	distance_type _distance;
};

struct EatAction : IAction {
	EatAction(ICat* /*cat*/);
	virtual ACTION_T type() const override final;
};

struct SleepAction : IAction {
	SleepAction(ICat* /*cat*/);
	virtual ACTION_T type() const override final;
	virtual void sleep() const final;
};

struct ComposedAction : IAction {
	ComposedAction(ICat* /*cat*/);
	virtual ACTION_T type() const override final;
	const actions_type& actions() const;
	void push_back(IAction* /*action*/);
protected:
	actions_type _actions;
};

struct GoToAction : public ComposedAction {
	GoToAction(ICat* /*cat*/, const Object* /*object*/);
};

struct GoToSleepAction : public ComposedAction {
	GoToSleepAction(ICat* /*cat*/, const beds_type& /*type*/);
};

/* An interface for Cat. */
class ICat : public Object {
protected:
	CatConfig	_cfg;
	size_t		_eated_fishes;
	CRoom*		_room;
public:
	ICat(const CatConfig& /*cfg*/, CRoom* /*room*/);
	virtual ~ICat();

	virtual const size_t fishInStomach() const final;
	virtual const size_t stomachIsFull() const final;
	virtual const distance_type distance(coord /*p*/) const final;
	virtual CatConfig getConfig() const final;

	virtual IAction* Next(IAction* /*action*/) = 0;
};

/* functors for sorting */
struct by_distance{
	ICat* _cat;
	by_distance(ICat* /*cat*/);
	bool operator()(Object* /*object1*/, Object* /*object2*/) const;

};

struct by_volume{
	ICat* _cat;
	by_volume(ICat* /*cat*/);
	bool operator()(CPlate* /*plate1*/, CPlate* /*plate2*/) const;
};

#endif /* ICAT_H */