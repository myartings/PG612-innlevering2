#include "SliderWithText.h"

static const std::string debug_texture_path = "GUI/debug.png";
static const std::string slider_texture_path = "GUI/Slider_line.png";
static const std::string slider_knob_texture_path = "GUI/Slider_knob.png";

SliderWithText::SliderWithText(const std::string& name_label_path,
							  std::shared_ptr<GLUtils::Program> gui_program, 
							  glm::vec2 position)
	:label(name_label_path), slider(slider_texture_path), slider_knob(slider_knob_texture_path)
{

	label.set_position(glm::vec3(position.x, position.y+15, -5));
	
	slider.set_position(glm::vec3(position.x, position.y, -5));
	slider.set_scale(glm::vec2(0.6f));
	

	slider_knob.set_position(glm::vec3(slider.get_rect().x+(slider.get_rect().width/3.0f), position.y, -5));
	slider_knob.set_scale(glm::vec2(0.6f));

	glBindTexture(GL_TEXTURE_2D, 0);

	interacting = false;
	UpdateSliderValue();
}

SliderWithText::~SliderWithText()
{
}

void SliderWithText::Draw()
{
	label.Draw();
	slider.Draw();
	slider_knob.Draw();

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
		UpdateSliderValue();
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

float SliderWithText::get_slider_value()
{
	return slider_value;
}

void SliderWithText::UpdateSliderValue()
{

	slider_value = (slider_knob.get2d_position().x - slider.get_rect().x) / slider.get_rect().width;
	slider_value += 0.08f;
	if(slider_value < 0.0f)
		slider_value = 0.0f;
	else if(slider_value > 1.0f)
		slider_value = 1.0f;
	std::cout << slider_value << std::endl;
}

