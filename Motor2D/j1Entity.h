#ifndef __ModuleEntity_H__
#define __ModuleEntity_H__

#include "j1Module.h"
#include "j1Animation.h"
#include "p2Point.h"
#include "p2DynArray.h"
#include "j1Timer.h"
#include "PugiXml/src/pugixml.hpp"

//#define gravity -625
//#define DETECTION_MARGIN 350

struct SDL_Texture;

enum entity_state
{
	IDLE = 0,
	RIGHT,
	LEFT,
	CROUCHING,
	DASHING,
	JUMPING,
	STOP_JUMPING,
	FALLING,
};

enum entity_type
{
	PLAYER = 0,
	ALIEN,
	CHICKEN,
};

class Entity : public j1Module
{
public:

	Entity(const char* name);
	virtual ~Entity();

	bool Entity_Update(float dt);

	bool Calculate_Path();
	virtual void standardPath()
	{}
	virtual void followPath()
	{}

	void Entity_OnCollision(Collider* C1, Collider* C2);

public:

	p2Point<float>		position;
	p2Point<float>		initial_position;
	p2Point<float>		velocity;

	entity_state		state;
	
	bool				dead = false;
	bool				is_grounded = false;
	bool				flip = false;

	SDL_Texture*		graphics = nullptr;
	p2SString			spritesheet;

	//Path logic
	p2DynArray<iPoint>	entityPath;
	j1Timer				doStandardPath;
	bool				counting = false;
	bool				slowerPath = false;
	bool				god_mode = false;

	//Common animations	
	Animation*			current_anim;
	Animation			idle_anim;
	Animation			run_anim;
	Animation			jump_anim;
	Animation*			death = nullptr;

	Collider*			collider = nullptr;

	float				gravity;
	float				jump_force;

	entity_type			type;
	
};

#endif // !__ModuleEntity_H__