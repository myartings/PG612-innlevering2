#include "TextureLoader.h"
namespace TextureLoader
{
	void LoadTexture(GLuint* target_image, const std::string& image_to_load)
	{
		std::vector<float> data;

		ILuint ImageName;
		unsigned int width, height, components;

		ilGenImages(1, &ImageName); // Grab a new image name.
		ilBindImage(ImageName); 
		ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
		if (!ilLoadImage(image_to_load.c_str())) {
			ILenum e;
			std::stringstream error;
			while ((e = ilGetError()) != IL_NO_ERROR) {
				error << e << ": " << iluErrorString(e) << std::endl;
			}
			ilDeleteImages(1, &ImageName); // Delete the image name. 
			throw std::runtime_error(error.str());
		}

		width = ilGetInteger(IL_IMAGE_WIDTH); // getting image width
		height = ilGetInteger(IL_IMAGE_HEIGHT); // and height
		components = ilGetInteger(IL_IMAGE_CHANNELS);

		data.resize(width*height*components);

		if(components == 3)
			ilCopyPixels(0, 0, 0, width, height, 1, IL_RGB, IL_UNSIGNED_BYTE, data.data());
		else if(components == 4)
			ilCopyPixels(0, 0, 0, width, height, 1, IL_RGBA, IL_UNSIGNED_BYTE, data.data());

		ilDeleteImages(1, &ImageName); // Delete the image name. 

		glBindTexture(GL_TEXTURE_2D, *target_image);
		if(components == 3)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data.data());
		else if(components == 4)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.data());
	}
}
