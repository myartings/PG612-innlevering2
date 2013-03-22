#ifndef GUI_Util_H
#define GUI_Util_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform2.hpp>
#include <gl/glew.h>

#include <IL/il.h>
#include <IL/ilu.h>
#include <iostream>
#include <strstream>
#include <vector>
#include <stdexcept>

#include "Game_Constants.h"
#include "GLUtils/GLUtils.hpp"

using std::cerr;
using std::endl;
using GLUtils::checkGLErrors;

/**
* The namespace contains a few wrapper functions for glm which 
* makes sure all transforms are happening on a per-pixel-on-the-screen
* basis. Since GUI is drawn orthogonally between 0 and screen width/height,
* this is much more intuitive than handling positions the same way you do 
* for objects being rendered normally.
*/
namespace gui
{
	struct Texture
	{
		Texture()
		{
			image = -1;
			width = -1;
			height = -1;
			components = -1;
		}

		GLuint image;
		GLuint width;
		GLuint height;
		GLuint components;
	};
	
	class GUITexture
	{
	public:
		GUITexture();
		GUITexture(std::string& texture_path);
		~GUITexture();

		Texture texture;
		glm::vec3 position;
		glm::vec3 scale;

		void Draw(std::shared_ptr<GLUtils::Program> gui_program);

		/**
		* Translates this GUITexture with the param vec2
		*/
		void translate(glm::vec2 v);

		/**
		* Translates this GUITexture with the param vec3
		*/
		void translate(glm::vec3 v);

		/**
		* Sets the position of this GUITexture to the param vec2
		* When using a vec2 rather than a vec3 the depth of the 
		* texture is defaulted to -5.0f;
		*/
		void set_position(glm::vec2 v);

		/**
		* Sets the position of this GUITexture to the param vec2
		*/
		void set_position(glm::vec3 v);
		
		void set_scale(glm::vec2 v);

	private:
		glm::mat4 model_matrix;

	};

	typedef std::shared_ptr<GUITexture> GUITexture_ptr;
	
	/**
	* Builds a 4 * 4 model matrix for a gui texture.
	* 
	* @param tex_width width of the texture the matrix is to be used with
	* @param tex_height height of the texture the matrix is to be used with
	*/
	glm::mat4 gen_gui_model_matrix(GLuint tex_width, GLuint tex_height);

	/**
	* Builds a translation 4 * 4 matrix created from a vector of 3 components.
	* The translation vector values are divided by the window width and height
	* to give the values of the translation a 1-1 ratio with a pixel.
	* 
	* @param m Input matrix multiplied by this translation matrix.
	* @param v Coordinates of a translation vector.
	*/
	glm::mat4 screencoord_translate(glm::mat4& m, glm::vec3& v);

	/**
	* Generates a GL_TEXTURE_2D with glTexParameteri values suiting GUI textures
	*/
	GLuint create_texture();

	/**
	* Loads the desired texture using DevIL.
	*
	* @returns a Texture object containing openGL image ID, and the
	* width, height and number of components of the image
	*/
	Texture LoadTexture(const std::string& image_to_load);

	/**
	* Loads the desired texture using DevIL.
	*
	* @param texture_path path to the texture to load, including name and file extension
	* @returns a GUITexture ptr to an object containing the texture, ready for use.
	*/
	GUITexture_ptr load_gui_texture(const std::string& texture_path);
}
#endif // GUI_Util_H
