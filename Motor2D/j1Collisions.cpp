#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Player.h"
#include "j1Collisions.h"
#include "j1Map.h"
#include "j1EntityManager.h"
#include "p2Log.h"

#include "Brofiler/Brofiler.h"

j1Collisions::j1Collisions()
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[COLLIDER_UNPENETRABLE][COLLIDER_UNPENETRABLE] = false;
	matrix[COLLIDER_UNPENETRABLE][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_UNPENETRABLE][COLLIDER_PENETRABLE] = false;
	matrix[COLLIDER_UNPENETRABLE][COLLIDER_SPIKES] = false;
	matrix[COLLIDER_UNPENETRABLE][COLLIDER_WIN] = false;
	matrix[COLLIDER_UNPENETRABLE][COLLIDER_ENEMY] = false;


	matrix[COLLIDER_PLAYER][COLLIDER_UNPENETRABLE] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_PENETRABLE] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_SPIKES] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_WIN] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY] = true;

	matrix[COLLIDER_PENETRABLE][COLLIDER_UNPENETRABLE] = false;
	matrix[COLLIDER_PENETRABLE][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PENETRABLE][COLLIDER_PENETRABLE] = false;
	matrix[COLLIDER_PENETRABLE][COLLIDER_SPIKES] = false;
	matrix[COLLIDER_PENETRABLE][COLLIDER_WIN] = false;
	matrix[COLLIDER_PENETRABLE][COLLIDER_ENEMY] = false;

	matrix[COLLIDER_ATTACK][COLLIDER_ATTACK] = false;
	matrix[COLLIDER_ATTACK][COLLIDER_UNPENETRABLE] = false;
	matrix[COLLIDER_ATTACK][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_ATTACK][COLLIDER_PENETRABLE] = false;
	matrix[COLLIDER_ATTACK][COLLIDER_SPIKES] = false;
	matrix[COLLIDER_ATTACK][COLLIDER_WIN] = false;
	matrix[COLLIDER_ATTACK][COLLIDER_ENEMY] = true;

	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_ATTACK] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_PENETRABLE] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_UNPENETRABLE] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_SPIKES] = false;


}
bool j1Collisions::Awake()
{
	return true;
}
// Destructor
j1Collisions::~j1Collisions()
{}

bool j1Collisions::PreUpdate()
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i) //Remove colliders
	{
		if (colliders[i] != nullptr && colliders[i]->to_delete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

// Called before render is available
bool j1Collisions::Update(float dt)
{
	
	
	Collider* c1;
	Collider* c2;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if (colliders[i] == nullptr)
			continue;

		c1 = colliders[i];
		c1->Update();

		// avoid checking collisions already checked
		for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if (colliders[k] == nullptr)
				continue;

			c2 = colliders[k];
			c2->Update();

			if (c1->CheckCollision(c2->rect) == true)
			{
				if (matrix[c1->type][c2->type] && c1->callback)
				{
					c1->callback->Entity_OnCollision(c1, c2);
				}
				if (matrix[c2->type][c1->type] && c2->callback)
				{
					c2->callback->Entity_OnCollision(c2, c1);
				}
					
			}
		}
	}

	return true;
}

bool j1Collisions::PostUpdate()
{
	DebugDraw();

	return true;
}

void j1Collisions::DebugDraw()
{

	if (debug == false)
	{
		return;
	}
	Uint8 alpha = 80;
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			continue;
		}
		switch (colliders[i]->type)
		{
		case COLLIDER_NONE: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
		case COLLIDER_UNPENETRABLE: // blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
		case COLLIDER_PLAYER: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;
		case COLLIDER_PENETRABLE: // cyan
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;
		case COLLIDER_SPIKES: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
		case COLLIDER_WIN: // orange
			App->render->DrawQuad(colliders[i]->rect, 255, 140, 0, alpha);
			break;
		case COLLIDER_ATTACK: //yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 140, alpha);
			break;
		case COLLIDER_ENEMY:
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 255, alpha);
		}
	}
}

// Called before quitting
bool j1Collisions::CleanUp()
{
	LOG("Freeing all colliders");

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* j1Collisions::AddCollider(SDL_Rect rect, COLLIDER_TYPE type, j1Module* callback)
{
	Collider* ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, callback);
			break;
		}
	}

	return ret;
}

bool j1Collisions::EraseCollider(Collider* collider)
{
	if (collider != nullptr)
	{
		// we still search for it in case we received a dangling pointer
		for (uint i = 0; i < MAX_COLLIDERS; ++i)
		{
			if (colliders[i] == collider)
			{
				collider->to_delete = true;
				break;
			}
		}
	}


	return false;
}

// -----------------------------------------------------

bool Collider::CheckCollision(const SDL_Rect& r) const
{
	return (rect.x < r.x + r.w &&
		rect.x + rect.w > r.x &&
		rect.y < r.y + r.h &&
		rect.h + rect.y > r.y);
}

bool Collider::Update()
{
	return true;
}