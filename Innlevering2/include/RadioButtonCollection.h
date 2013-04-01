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

namespace gui
{
	class RadioButtonEntry
	{
	public:
		RadioButtonEntry(std::function<void()> selected_callback,
						bool is_active, const std::string& label_path);
					

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
		RadioButtonCollection(std::vector<RadioButtonEntry> _radio_buttons, 
								glm::vec2 position, glm::vec2 scale);
		RadioButtonCollection(std::vector<RadioButtonEntry> _radio_buttons, glm::vec2 position, 
								glm::vec2 scale, std::string collection_label_path);

		~RadioButtonCollection();
	
		/**
		* Performs updates based on the mouse click
		*/
		void OnClick(glm::vec2& mouse_pos);

		void Draw();

		/**
		* Uses the param int as an index in the radio button collection
		* and sets that entry active if it exist
		*/
		void SetActive(unsigned int entrynumber);

	protected:

	private:
		std::vector<RadioButtonEntry> radio_buttons;
		glm::vec2 position;
		GUITexture* name_label;
	};
};



#endif // RadioButtonCollection_h__