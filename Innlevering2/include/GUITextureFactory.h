/********************************************************************
    created:    29:3:2013   16:23
    filename:   GUITextureFactory.h
    author:     Kristian Skarseth
    
	purpose:	Load and handle textures. Loading a texture uploads it directly
				to the gpu, and stores the Texture in a map, where it can be
				accessed with the original texturePath as key.

				Using a singleton for this class as we only ever want one copry of it, 
				and it can be convenient to publically access it from several classes.

*********************************************************************/
#ifndef GUITextureFactory_h__
#define GUITextureFactory_h__

#include <string>
#include <map>

#include <iostream>
#include <IL/il.h>
#include <IL/ilu.h>
#include <vector>
#include <GL/glew.h>
#include <sstream>
#include <vector>
#include <assert.h>
#include <stdexcept>

#include "GUI_Util.h"
#include "GLUtils/GLUtils.hpp"
#include "GameException.h"

using GLUtils::checkGLErrors;

namespace gui
{
	class GUITextureFactory
	{
	public:
		static GUITextureFactory* Inst();
	
		void Init(std::shared_ptr<GLUtils::Program> gui_program, GLuint gui_vao);

		/*
		* Returns the Texture for the textureName. Can be directly
		* bound to openGL for use. 
		*
		* If the texture has not already been loaded, the class will
		* attempt to load it. If the loading fails, the function 
		* returns -1.
		*/
		Texture GetTexture(const std::string& texture_name);

		/*
		* Attempts to load and store the texture on the texturepath.
		* If it's successfull, the openGL ID is returned.
		*
		* If the loading fails, the function returns -1. 
		*/
		Texture LoadTexture(const std::string& texture_path);

		//The GUI shader program
		std::shared_ptr<GLUtils::Program> gui_program;
		
		// The GUI VAO object holding states for rendering GUI stuff
		GLuint gui_vao;

	private:
		GUITextureFactory();
		~GUITextureFactory();

		Texture* TryFindInMap(const std::string& texture_path);

		// Our map of textureIDs
		std::map<std::string, Texture> texture_map;


	};
};


#endif // GUITextureFactory_h__