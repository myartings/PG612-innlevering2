/********************************************************************
    created:    22:3:2013   19:20
    filename:   GUITexture.h
    author:     Kristian Skarseth
    
    purpose:    
*********************************************************************/
#ifndef GUITexture_h__
#define GUITexture_h__


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform2.hpp>
#include <gl/glew.h>

#include "GUI_Util.h"
#include "GUITextureFactory.h"
/**
* The namespace contains functions to make "GUI" texture displaying easier.
*/
namespace gui
{
	/**
	* A class for drawing, scaling and translating textures in GUI space.
	* A GUITexture should always be drawn with am orthogonal camera.
	*/
	class GUITexture
	{
	public:
		GUITexture(const std::string& texture_path);
		~GUITexture();

		/**
		* Draws the GUITexture to screen.
		*
		* @param gui_program the shader program used to draw GUI stuff
		*/
		void Draw();

		/**
		* Translates this GUITexture with the param vec2
		*/
		void translate(glm::vec2& v);

		/**
		* Translates this GUITexture with the param vec3
		*/
		void translate(glm::vec3& v);

		/**
		* Sets the position of this GUITexture to the param vec2
		* When using a vec2 rather than a vec3 the depth of the 
		* texture is defaulted to -5.0f;
		*/
		void set_position(glm::vec2& v);

		/**
		* Sets the position of this GUITexture to the param vec3
		*/
		void set_position(glm::vec3& v);
		
		/**
		* Sets the scale of this GUITexture using the param vec2
		*/
		void set_scale(glm::vec2& v);

		/**
		* Returns true if the param vector is within/colliding with 
		* this GUITextures bounds
		*
		* @param v a 2d point on the screen
		* @return true when the param vector is within this GUITexture
		*/
		bool contains(glm::vec2& v);

		/**
		* @returns the position of this GUITexture
		*/
		glm::vec3& get_position();

		/**
		* @returns the xy position of this GUITexture
		*/
		glm::vec2& get2d_position();

		/**
		* @returns the rect representing this GUITextures bounds on the screen
		*/
		gui::Rect& get_rect();

	private:
		glm::mat4 model_matrix;
		Texture texture;
		glm::vec3 position;
		glm::vec2 position_2d;

		glm::vec3 dimensions;
		glm::vec3 scale;
		Rect rect;
	};

	typedef std::shared_ptr<GUITexture> GUITexture_ptr;
}

#endif // GUITexture_h__