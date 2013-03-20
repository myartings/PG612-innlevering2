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
	/**
	* Loads the desired texture using DevIL.
	* The pixels are copied to the image represented
	* with the target_image. TextureParameters should 
	* already be set on the target_image.
	*/
	void LoadTexture(GLuint* target_image, const std::string& image_to_load);
	
}

#endif // TextureLoader_H
