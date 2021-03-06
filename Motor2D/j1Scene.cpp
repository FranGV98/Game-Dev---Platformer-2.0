#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1Scene.h"
#include "j1FadeToBlack.h"
#include "j1Collisions.h"
#include "j1GUI.h"
#include "j1Fonts.h"
#include "j1UIScene.h"

j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;

	soundtrack[0] = config.child("Music1").attribute("source").as_string();

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	App->map->Load("Level1.tmx");
	App->audio->PlayMusic(soundtrack[0].GetString(), -1);

	
	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		App->SaveGame("save_game.xml");

	if (App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		App->LoadGame("save_game.xml");


	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
	{
		App->fade_to_black->FadeToBlack("Level1.tmx", 3.0f);
	}
	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
	{
		App->fade_to_black->FadeToBlack("Level2.tmx",3.0f);
	}
	if (App->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN)
	{
		if (App->map->data.map_name == "Level1.tmx")
			App->fade_to_black->FadeToBlack("Level1.tmx", 3.0f);
		if (App->map->data.map_name == "Level2.tmx")
			App->fade_to_black->FadeToBlack("Level2.tmx", 3.0f);
	}
	if (App->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
	{
		App->collisions->debug = !App->collisions->debug;
	}
	App->map->Draw();

	int x, y;
	App->input->GetMousePosition(x, y);
	iPoint map_coordinates = App->map->WorldToMap(x - App->render->camera.x, y - App->render->camera.y);
	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{

	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	{
		App->pause = true;
		App->ui_scene->loadMenu(INGAME_MENU);
	}

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}
