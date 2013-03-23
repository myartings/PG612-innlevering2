#include "SliderWithText.h"

//gui::GUITexture SliderWithText::slider_texture;
//gui::GUITexture SliderWithText::slider_knob_texture;
GLuint SliderWithText::gui_vbo = -1;
GLuint SliderWithText::gui_vao = -1;

static const std::string debug_texture_path = "GUI/debug.png";
static const std::string slider_texture_path = "GUI/Slider_line.png";
static const std::string slider_knob_texture_path = "GUI/Slider_knob.png";

SliderWithText::SliderWithText(const std::string& name_label_path,
							  std::shared_ptr<GLUtils::Program> gui_program, 
							  glm::vec2 position)
	:label(name_label_path), slider(slider_texture_path), slider_knob(slider_knob_texture_path)
{
	if(gui_vao == -1 && gui_vbo == -1)
	GenerateGUI_VBO_VAO(gui_program);

	label.set_position(glm::vec3(position.x, position.y+15, -5));
	
	slider.set_position(glm::vec3(position.x, position.y, -5));
	slider.set_scale(glm::vec2(0.6f));
	
	slider_knob.set_position(glm::vec3(position.x, position.y, -5));

	slider_knob.set_scale(glm::vec2(0.6f));

	glBindTexture(GL_TEXTURE_2D, 0);

	interacting = false;
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
	glBindVertexArray(gui_vao);
	
	label.Draw(gui_program);
	slider.Draw(gui_program);
	slider_knob.Draw(gui_program);
	
	glBindVertexArray(0);
	CHECK_GL_ERRORS();
}

void SliderWithText::Update( float delta_time, glm::vec2& mouse_pos )
{
	if(interacting)
	{
		glm::vec2 lowleft_mousepos = glm::vec2(mouse_pos.x, window_height-mouse_pos.y);
		if(slider.get_rect().x < lowleft_mousepos.x && slider.get_rect().x + slider.get_rect().width > lowleft_mousepos.x)
		{
			if(lowleft_mousepos.x != previous_mouse_pos.x)
			{
				glm::vec2 new_knob_pos = slider_knob.get2d_position();
				new_knob_pos.x += lowleft_mousepos.x - previous_mouse_pos.x;

				slider_knob.set_position(new_knob_pos);
			}
			previous_mouse_pos = lowleft_mousepos;
		}
		
	}
}

bool SliderWithText::BeginInteraction( glm::vec2& mouse_pos )
{
	previous_mouse_pos = glm::vec2(mouse_pos.x, window_height-mouse_pos.y);

	if(slider_knob.contains(previous_mouse_pos))
	{
		interacting = true;
		return true;
	}
	else
		return false;
}

void SliderWithText::EndInteraction( glm::vec2& mouse_pos )
{
	interacting = false;
}

