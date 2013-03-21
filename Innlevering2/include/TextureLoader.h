#ifndef TextureLoader_H
#define TextureLoader_H

#include "GLUtils/GLUtils.hpp"

#include <IL/il.h>
#include <IL/ilu.h>
#include <iostream>
#include <strstream>
#include <vector>
#include <stdexcept>

using std::cerr;
using std::endl;
using GLUtils::checkGLErrors;

namespace TextureLoader
{
	struct Image
	{
		Image()
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

	/**
	* Loads the desired texture using DevIL.
	* The pixels are copied to the image represented
	* with the target_image. TextureParameters should 
	* already be set on the target_image.
	*/
	void LoadTexture(Image* target_image, const std::string& image_to_load);
	
}

#endif // TextureLoader_H
