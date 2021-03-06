#ifndef __j1UISCENE_H__
#define __j1UISCENE_H__

#include "j1Module.h"
#include "p2List.h"

#define OFFSET_TO_CENTER 450

class Button;
class UI_element;

enum menu_id
{
	NO_MENU,

	START_MENU,
	SETTINGS_MENU,
	INGAME_MENU,
	PAUSE_MENU,
	CREDITS_MENU,
	END_MENU
};

struct menu
{
	menu(menu_id id) : id(id)
	{}

	p2List<UI_element*> elements;
	menu_id id;
};

struct settings_values
{
	bool fullscreen = false;
	float music = 0.5f;
	float fx = 0.5f;
};

class j1UIScene : public j1Module
{
public:

	j1UIScene();
	~j1UIScene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate(float dt);

	// Called before quitting
	bool CleanUp();

	bool UIEvent(UI_element* element, event_type event_type);

	bool loadMenu(menu_id id);
	menu* getMenu(menu_id id) const;

	void applySettings(settings_values values);

	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;

public:

	p2List<menu*> menus;
	menu* current_menu = nullptr;
	menu_id previous_menu;

	settings_values startValues;
	settings_values newValues;
	settings_values defaultValues;

	p2SString			menu_music[1];
};

#endif // !__j1UISCENE_H__
