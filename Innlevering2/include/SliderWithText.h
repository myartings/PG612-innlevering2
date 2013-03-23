/********************************************************************
    created:    20:3:2013   18:28
    filename:   SliderWithText.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef SliderWithText_h__
#define SliderWithText_h__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform2.hpp>
#include <gl/glew.h>

#include <string>

#include "GUI_Util.h"
#include "GUITexture.h"

using namespace gui;



class SliderWithText
{
public:
    SliderWithText(const std::string& name_label_path, 
				   std::shared_ptr<GLUtils::Program> gui_program, 
				   glm::vec2 position);

    ~SliderWithText();

	void Draw(glm::vec2 position, GLuint& quad_fbo, 
			std::shared_ptr<GLUtils::Program> gui_program);

	/**
	* Sets the Sliders state to updating. Mouse input after this function
	* is called will affect the slider knobs position if Update is called.
	*
	* @param mouse_pos position of the mouse in SDL event.motion coordinates
	*/
	bool BeginInteraction(glm::vec2& mouse_pos);
	
	/**
	* Sets the sliders state to not updating. Mouse input after this function
	* is called will not affect the slider knobs position.
	*
	* @param mouse_pos position of the mouse in SDL event.motion coordinates
	*/
	void EndInteraction(glm::vec2& mouse_pos);

	/**
	* Updates the position of the slider based on the mouse position.
	* If BeginInteraction has not been called since startup or previous
	* EndInteraction call, the position will not be updated.
	*
	* @param delta_time time since last game update
	* @param mouse_pos position of the mouse in SDL event.motion coordinates
	*/
	void Update(float delta_time, glm::vec2& mouse_pos);

private:
	GUITexture slider;
	GUITexture slider_knob;
	GUITexture label;

	static GLuint gui_vbo, gui_vao;
	
	void GenerateGUI_VBO_VAO(std::shared_ptr<GLUtils::Program> gui_program);

	
	bool interacting;
	glm::vec2 previous_mouse_pos;

	
};

#endif // SliderWithText_h__