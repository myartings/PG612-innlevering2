#include "TextureLoader.h"
namespace TextureLoader
{
	void LoadTexture(Image* target_image, const std::string& image_to_load)
	{
		std::vector<float> data;

		ILuint ImageName;
		
		ilGenImages(1, &ImageName); // Grab a new image name.
		ilBindImage(ImageName); 
		ilEnable(IL_ORIGIN_SET);
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
	
		target_image->width = ilGetInteger(IL_IMAGE_WIDTH); // getting image width
		target_image->height = ilGetInteger(IL_IMAGE_HEIGHT); // and height
		target_image->components = ilGetInteger(IL_IMAGE_CHANNELS);

		data.resize(target_image->width*target_image->height*target_image->components);

		if(target_image->components == 3)
			ilCopyPixels(0, 0, 0, target_image->width, target_image->height, 1, IL_RGB, IL_UNSIGNED_BYTE, data.data());
		else if(target_image->components == 4)
			ilCopyPixels(0, 0, 0, target_image->width, target_image->height, 1, IL_RGBA, IL_UNSIGNED_BYTE, data.data());

		ilDeleteImages(1, &ImageName);
		ilDisable(IL_ORIGIN_SET);
		glBindTexture(GL_TEXTURE_2D, target_image->image);

		if(target_image->components == 3)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, target_image->width, target_image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, data.data());
		else if(target_image->components == 4)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, target_image->width, target_image->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.data());
	}
}
