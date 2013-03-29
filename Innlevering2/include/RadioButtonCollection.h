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
	std::function<void()> on_selected;
	GUITexture gui_texture;
};

class RadioButtonCollection
{
public:
    RadioButtonCollection(std::vector<RadioButtonEntry> radio_buttons);
    ~RadioButtonCollection();

	void Update(glm::vec2& mouse_pos);

	void Draw(std::shared_ptr<GLUtils::Program> gui_program);

protected:

private:

};

#endif // RadioButtonCollection_h__