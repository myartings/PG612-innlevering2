#include "RadioButtonCollection.h"
namespace gui
{
	RadioButtonCollection::RadioButtonCollection( std::vector<RadioButtonEntry> _radio_buttons, glm::vec2 position, glm::vec2 scale )
	{
		radio_buttons = _radio_buttons;
		name_label = NULL;
		float offset = 0;

		for(unsigned int i = 0; i < radio_buttons.size(); i++)
		{
			radio_buttons.at(i).Init(glm::vec2(position.x, position.y-offset), scale);
			offset += radio_buttons.at(i).label_texture.get_rect().height;
		}
	}

	RadioButtonCollection::RadioButtonCollection( std::vector<RadioButtonEntry> _radio_buttons, glm::vec2 position, 
		glm::vec2 scale, std::string collection_label_path )
	{
		radio_buttons = _radio_buttons;
		name_label = new GUITexture(collection_label_path);
		name_label->set_position(position);
		name_label->set_scale(scale);
		float offset = name_label->get_rect().height;

		for(unsigned int i = 0; i < radio_buttons.size(); i++)
		{
			radio_buttons.at(i).Init(glm::vec2(position.x, position.y-offset), scale);
			offset += radio_buttons.at(i).label_texture.get_rect().height;
		}
	}

	RadioButtonCollection::~RadioButtonCollection()
	{
		if(name_label)
		{
			delete name_label;
			name_label = NULL;
		}
	}

	void RadioButtonCollection::OnClick( glm::vec2& mouse_pos)
	{
		glm::vec2 lowleft_mousepos = glm::vec2(mouse_pos.x, window_height-mouse_pos.y);
		for(unsigned int i = 0; i < radio_buttons.size(); i++)
		{
			if(radio_buttons.at(i).label_texture.contains(lowleft_mousepos))
			{
				if(radio_buttons.at(i).active != true)
				{
					for(unsigned int x = 0; x < radio_buttons.size(); x++)
						radio_buttons.at(x).active = false;

					radio_buttons.at(i).active = true;
					radio_buttons.at(i).on_selected();
				}

			}
		}
	}

	void RadioButtonCollection::Draw()
	{
		if(name_label)
			name_label->Draw();

		for(unsigned int i = 0; i < radio_buttons.size(); i++)
			radio_buttons.at(i).Draw();
	}

	void RadioButtonCollection::SetActive( unsigned int entrynumber )
	{
		if(entrynumber < radio_buttons.size())
		{
			for(unsigned int i = 0; i < radio_buttons.size(); i++)
				radio_buttons.at(i).active = false;
			radio_buttons.at(entrynumber).active = true;
		}
	}

	/*----------------------------------------*/
	/*-------RadioButtonEntry functions-------*/
	/*----------------------------------------*/

	static const std::string activepath = "GUI/active.png";
	static const std::string inactivepath = "GUI/inactive.png";
	RadioButtonEntry::RadioButtonEntry( std::function<void()> selected_callback, 
		bool is_active, const std::string& label_path )
		: label_texture(label_path), active_texture(activepath),
		inactive_texture(inactivepath)
	{
		on_selected = selected_callback;
		active = is_active;
	}

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
}
