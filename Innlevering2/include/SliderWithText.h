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
    SliderWithText(const std::string& name_label_path,std::shared_ptr<GLUtils::Program> gui_program);
    ~SliderWithText();

	void Draw(glm::vec2 position, GLuint& quad_fbo, 
			std::shared_ptr<GLUtils::Program> gui_program);

	bool Update(float delta_time, glm::vec2& mouse_pos);

private:
	GUITexture slider;
	GUITexture slider_knob;
	GUITexture label;

	static GLuint gui_vbo, gui_vao;
	
	void GenerateGUI_VBO_VAO(std::shared_ptr<GLUtils::Program> gui_program);

	//gui::GUITexture label_texture;
	//glm::mat4 model_matrix;
};

#endif // SliderWithText_h__