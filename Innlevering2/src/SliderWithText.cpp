#include "SliderWithText.h"

//gui::GUITexture SliderWithText::slider_texture;
//gui::GUITexture SliderWithText::slider_knob_texture;
GLuint SliderWithText::gui_vbo = -1;
GLuint SliderWithText::gui_vao = -1;

static const std::string debug_texture_path = "GUI/debug.png";
static const std::string slider_texture_path = "GUI/Slider_line.png";
static const std::string slider_knob_texture_path = "GUI/Slider_knob.png";

SliderWithText::SliderWithText(const std::string& name_label_path,std::shared_ptr<GLUtils::Program> gui_program)
	:label(name_label_path), slider(slider_texture_path), slider_knob(slider_knob_texture_path)
{
	if(gui_vao == -1 && gui_vbo == -1)
	GenerateGUI_VBO_VAO(gui_program);

	label.set_position(glm::vec3(800, 100, -5));
	label.set_scale(glm::vec2(0.7f));
	slider.set_position(glm::vec3(800, 0, -5));
	slider.set_scale(glm::vec2(0.7f));
	slider_knob.set_position(glm::vec3(800, 0, -5));
	slider_knob.set_scale(glm::vec2(0.7f));
	glBindTexture(GL_TEXTURE_2D, 0);
}

SliderWithText::~SliderWithText()
{
}


void SliderWithText::GenerateGUI_VBO_VAO(std::shared_ptr<GLUtils::Program> gui_program)
{
	glGenVertexArrays(1, &gui_vao);
	glBindVertexArray(gui_vao);
	static float positions[8] = {
		/*-1.0, 1.0,
		-1.0, -1.0,
		1.0, 1.0,
		1.0, -1.0*/
		0.0, 1.0,
		0.0, 0.0,
		1.0, 1.0,
		1.0, 0.0
	};

	glGenBuffers(1, &gui_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, gui_vbo);
	glBufferData(GL_ARRAY_BUFFER, 4*2*sizeof(float), &positions[0], GL_STATIC_DRAW);
	gui_program->setAttributePointer("in_Position", 2, GL_FLOAT, GL_FALSE, 0, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SliderWithText::Draw( glm::vec2 position, GLuint& quad_fbo,
						std::shared_ptr<GLUtils::Program> gui_program)
{
	//gui_program->use();

	////Bind the textures before rendering
	//glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(gui_vao);
	
	label.Draw(gui_program);
	slider.Draw(gui_program);
	slider_knob.Draw(gui_program);
	CHECK_GL_ERRORS();
}

bool SliderWithText::Update( float delta_time, glm::vec2& mouse_pos )
{
	glm::vec2 lowleft_mousepos = glm::vec2(mouse_pos.x, window_height-mouse_pos.y);
	std::cout << "x: " << lowleft_mousepos.x << "  y: " << lowleft_mousepos.y << std::endl;
	if(slider_knob.contains(lowleft_mousepos))
	{
		std::cout << "inside"<< std::endl;
		return true;
	}
	return false;//return true if we are updating the slider
}

