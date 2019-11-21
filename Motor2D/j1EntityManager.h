#ifndef __ENTITY_MANAGER__
#define __ENTITY_MANAGER__

#include "j1Module.h"
#include "p2List.h"
#include "j1Entity.h"


struct SDL_Texture;

class j1EntityManager : public j1Module
{
public:

	j1EntityManager();
	~j1EntityManager();

	bool Awake(pugi::xml_node&);
	bool Start();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();


	void DeleteEntity(Entity* entity_to_delete);
	Entity* createEntity(entity_type type, int x, int y, int id = 0);
	Entity* getPlayer() const;


	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;

public:

	p2List<Entity*> entities;
	pugi::xml_node config;


	SDL_Texture* path_marker = nullptr;
	bool draw_path = false;
};

#endif // __ENTITY_MANAGER__
