#ifndef ICAT_H
#define ICAT_H

#include <string>
#include <vector>

enum class ACTION_T{
	NO_ACTION = 0,
	MOVE = 1,
	ROTATE,	// TODO 01: may be later
	EAT = 3,
	SLEEP = 4,
	COMPOSED = 10
};

class							ICat;
class							IAction;
class							IRoom;
struct							coord;
struct							CPlate;
struct							CBasket;
struct							CatConfig;

struct coord{
	size_t x, y;
};

struct Object{
	coord _position;
	virtual const coord& position() const final;
};

struct CPlate : public Object {
	size_t nr_fishes;
};

struct CBasket : public Object {
};

typedef std::vector<IAction*>	actions_type;
typedef actions_type::iterator	actions_iterator;
typedef std::vector<CPlate*>		plates_type;
typedef plates_type::iterator	plates_iterator;
typedef std::vector<ICat*>		cats_type;
typedef cats_type::iterator		cats_iterator;
typedef std::vector<CBasket*>		beds_type;
typedef beds_type::iterator		beds_iterator;

// typedef size_t					angle_type; // TODO 01: may be later
typedef double					distance_type;
//typedef size_t					distance_type;

struct CatConfig{
	std::string name;
	std::string author;
	size_t stomach_volume;
	size_t sleep_speed; // stomach speed clearing
	size_t eat_speed; // stomach speed filling
	size_t speed;
//	size_t rotation_speed; // TODO 01: may be later
};

// an iterface for action
class IAction{
public:
	IAction(ICat* cat);
	virtual ACTION_T type() const = 0;
protected:
	virtual const CatConfig catConfig() const final;
	ICat* _cat;
};

// move action
struct MoveAction : public IAction{
	MoveAction(ICat* c, distance_type t);
	virtual ACTION_T type() const override final;
	distance_type distance() const;
	void move();
protected:
	distance_type _distance;
};

// // TODO 01: may be later
//struct RotateAction : IAction{
//	RotateAction(ICat* c, angle_type a);
//	virtual ACTION_T type() const override final;
//	angle_type angle() const;
//	void rotate();
//protected:
//	angle_type _angle;
//};

struct EatAction : IAction{
	EatAction(ICat*);
	virtual ACTION_T type() const override final;
};

struct SleepAction : IAction{
	SleepAction(ICat*);
	virtual ACTION_T type() const override final;
	virtual void sleep() const final;
};

struct ComposedAction : IAction{
	ComposedAction(ICat*);
	virtual ACTION_T type() const override final;
	const actions_type& actions() const;
	void push_back(IAction* ac);
protected:
	actions_type _actions;
};

struct GoToAction : public ComposedAction {
	GoToAction(ICat*, const Object*);
};

struct GoHomeAction : public ComposedAction{
	GoHomeAction(ICat*, const beds_type&);
};

/* room interface */
class IRoom{
public:
	virtual const plates_type& plates() const = 0;
	virtual const cats_type& cats() const = 0;
	virtual const beds_type& beds() const = 0;
};

/* An interface for Cat. */
class ICat : public Object {
protected:
	CatConfig	_cfg;
	size_t		_eated_fishes;
//	angle_type	_angle;
	IRoom*		_room;
public:
	ICat(const CatConfig& cfg, IRoom* room);
	virtual ~ICat();

	virtual const size_t fishInStomach() const final;
	virtual const size_t stomachIsFull() const final;
	virtual const distance_type distance(coord p) const final;
//	virtual const angle_type angle(coord p) const final;
	virtual CatConfig getConfig() const final;

	virtual IAction* Next(IAction*) = 0;
};

/* functors for sorting */
struct by_distance{
	ICat* cat;
	by_distance(ICat*);
	bool operator()(Object*, Object*) const;

};

struct by_volume{
	ICat* cat;
	by_volume(ICat*);
	bool operator()(CPlate*, CPlate*) const;
};

//struct by_angle{
//	ICat* cat;
//	by_angle(ICat*);
//	bool operator()(Object*, Object*) const;
//};
#endif /* ICAT_H */