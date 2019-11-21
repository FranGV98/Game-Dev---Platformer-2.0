#pragma once
#ifndef __j1PLAYER_H__
#define __j1PLAYER_H__

#include "j1Module.h"
#include "j1Animation.h"
#include "j1App.h"
#include "p2Point.h"
#include "j1Entity.h"

struct SDL_Texture;
struct Collider;

class j1Player : public Entity
{

public:

	j1Player();
	virtual ~j1Player();
	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();
	bool Save(pugi::xml_node&) const;
	bool Load(pugi::xml_node&);

	void j1Player::Player_Colliding(Collider* c1, Collider* c2);
	void jumpMovement();
	void Load_Level();
	void Dash_Movement(float dt);
	bool PositionCameraOnPlayer();
	void God_Mode();
	/*iPoint dashDirection(player_state);*/ //Check the player direction to dash forwards


public:
	//player_state		pState;

	//SDL_Texture*		graphics = nullptr;
	//p2SString			spritesheet;
	
	//bool				is_dead;
	//bool				god_mode = false;
	bool				is_dashing;
	bool				is_jumping;
	bool				is_grounded;
	bool				able_superjump = false;



	int					jumpInit_pos;


	//p2Point<float>		position;
	//p2Point<float>		initial_position;


	//p2Point<float>		velocity;
	p2Point<float>		run_speed;
	p2Point<float>		max_speed;	
	p2Point<float>		dash_speed;

	//float				gravity;
	//float				jump_force;

	float				dash_acceleration;
	float				dash_startime = 0;
	float				dash_time;
	

	/*Collider*			player_col = nullptr;*/

	//Animation*			current_anim;
	//Animation			idle_anim;
	//Animation			run_anim;
	//Animation			jump_anim;

	Animation			crouch_anim;
	Animation			crouchwalk_anim;
	Animation			dash_anim;
	Animation			fall_anim;
	Animation			god_anim;
	Animation			attack_anim;

	p2SString			jump_SFX;
	p2SString			run_SFX;
	p2SString			dash_SFX;


};
#endif // __j1PLAYER_H__