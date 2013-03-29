#include "RadioButtonCollection.h"

RadioButtonCollection::RadioButtonCollection( std::vector<RadioButtonEntry> radio_buttons, glm::vec2 position )
{
	this->radio_buttons = radio_buttons;

	float offset = 0;
	for(unsigned int i = 0; i < radio_buttons.size(); i++)
	{
		radio_buttons.at(i).Init(glm::vec2(position.x, position.y+offset), glm::vec2(1, 1));
		offset -= radio_buttons.at(i).label_texture.OriginalTextureHeight();
	}
}

RadioButtonCollection::~RadioButtonCollection()
{
}

void RadioButtonCollection::OnClick( glm::vec2& mouse_pos)
{
	for(unsigned int i = 0; i < radio_buttons.size(); i++)
	{
		if(radio_buttons.at(i).label_texture.contains(mouse_pos))
		{
			if(radio_buttons.at(i).active != true)
			{
				radio_buttons.at(i).active = true;
				radio_buttons.at(i).on_selected();
			}
			
		}
	}
}

void RadioButtonCollection::Draw(  )
{

	for(unsigned int i = 0; i < radio_buttons.size(); i++)
		radio_buttons.at(i).Draw();
}

/*----------------------------------------*/
/*-------RadioButtonEntry functions-------*/
/*----------------------------------------*/

void RadioButtonEntry::Draw()
{
	label_texture.Draw();

	if(active)
		active_texture.Draw();
	else
		inactive_texture.Draw();
}

void RadioButtonEntry::Init( glm::vec2 position, glm::vec2 scale )
{	
	label_texture.set_position(position);
	active_texture.set_position(position);
	inactive_texture.set_position(position);

	label_texture.set_scale(scale);
	active_texture.set_scale(scale);
	inactive_texture.set_scale(scale);
}
