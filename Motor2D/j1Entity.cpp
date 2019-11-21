#include "j1Entity.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Collisions.h"
#include "j1Input.h"
#include "j1Audio.h"
#include "p2Log.h"
#include "j1EntityManager.h"
#include "j1Window.h"
#include "j1Textures.h"
#include "j1PathFinding.h"
#include "j1Player.h"
#include "Brofiler\Brofiler.h"

Entity::Entity(const char* name)
{
	velocity.x = 0;
	velocity.y = 0;

}

Entity::~Entity()
{
	App->tex->UnLoad(graphics);
	graphics = nullptr;
	if (collider != nullptr)
	{
		collider->to_delete = true;
		collider = nullptr;
	}
}

bool Entity::Entity_Update(float dt)
{
	return true;
}


void Entity::Entity_OnCollision(Collider* C1, Collider* C2)
{

}






