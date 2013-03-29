/********************************************************************
    created:    29:3:2013   16:16
    filename:   RadioButtonCollection.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef RadioButtonCollection_h__
#define RadioButtonCollection_h__

#include <functional>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform2.hpp>
#include <gl/glew.h>


#include "GUITexture.h"
using namespace gui;

struct RadioButtonEntry
{
	RadioButtonEntry(std::function<void()> selected_callback,
					bool is_active, const std::string& label_path)
					: label_texture(label_path), active_texture("GUI/active.png"),
					  inactive_texture("GUI/inactive.png")
	{
		on_selected = selected_callback;
		active = is_active;
	}

	void Draw();
	void Init(glm::vec2 position, glm::vec2 scale);

	std::function<void()> on_selected;

	GUITexture label_texture;
	GUITexture active_texture;
	GUITexture inactive_texture;

	bool active;
};

class RadioButtonCollection
{
public:
    RadioButtonCollection(std::vector<RadioButtonEntry> radio_buttons, glm::vec2 position);
    ~RadioButtonCollection();

	void OnClick(glm::vec2& mouse_pos);

	void Draw();

protected:

private:
	std::vector<RadioButtonEntry> radio_buttons;
	glm::vec2 position;
};

#endif // RadioButtonCollection_h__