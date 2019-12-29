#ifndef __GUISCROLLBAR__
#define __GUISCROLLBAR__

#include "j1Module.h"
#include "j1GUIelement.h"
#include "j1GUI.h"


class GUIscrollBar : public j1GUIelement
{
public:

	GUIscrollBar();
	~GUIscrollBar();


	bool Awake(pugi::xml_node&);
	bool Start();

	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	bool CleanUp();

	bool Load(pugi::xml_node&) { return true; };
	bool Save(pugi::xml_node&) const  const { return true; };
	void ScrollLimits();


	j1GUIelement* scrollButton = nullptr;
	float value;
};






#endif // !__GUISCROLLBAR__

