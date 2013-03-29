#include "GUITextureFactory.h"

namespace gui
{
	GUITextureFactory::GUITextureFactory()
	{
	}

	GUITextureFactory::~GUITextureFactory()
	{
	}

	GUITextureFactory* GUITextureFactory::Inst()
	{
		static GUITextureFactory* instance = new GUITextureFactory();
		return instance;
	}

	Texture GUITextureFactory::GetTexture( const std::string& texture_name )
	{
		Texture* t = TryFindInMap(texture_name);
		if(t != NULL)
			return *t;
		else
			return LoadTexture(texture_name);
	}

	Texture GUITextureFactory::LoadTexture( const std::string& texture_path )
	{
		Texture* t = TryFindInMap(texture_path);
		if(t != NULL)
			return *t;

		std::vector<float> data;
		Texture ret_tex;
		ILuint ImageName;
		ret_tex.image = create_texture();
		ilGenImages(1, &ImageName); // Grab a new image name.
		ilBindImage(ImageName); 
		ilEnable(IL_ORIGIN_SET);
		ilOriginFunc(IL_ORIGIN_LOWER_LEFT);

		if (!ilLoadImage(texture_path.c_str())) {
			ILenum e;
			std::stringstream error;
			while ((e = ilGetError()) != IL_NO_ERROR) {
				error << e << ": " << iluErrorString(e) << std::endl;
			}
			ilDeleteImages(1, &ImageName); // Delete the image name. 
			throw std::runtime_error(error.str());
		}

		ret_tex.width = ilGetInteger(IL_IMAGE_WIDTH); // getting image width
		ret_tex.height = ilGetInteger(IL_IMAGE_HEIGHT); // and height
		ret_tex.components = ilGetInteger(IL_IMAGE_CHANNELS);

		data.resize(ret_tex.width*ret_tex.height*ret_tex.components);

		if(ret_tex.components == 3)
			ilCopyPixels(0, 0, 0, ret_tex.width, ret_tex.height, 1, IL_RGB, IL_UNSIGNED_BYTE, data.data());
		else if(ret_tex.components == 4)
			ilCopyPixels(0, 0, 0, ret_tex.width, ret_tex.height, 1, IL_RGBA, IL_UNSIGNED_BYTE, data.data());

		ilDeleteImages(1, &ImageName);
		ilDisable(IL_ORIGIN_SET);
		glBindTexture(GL_TEXTURE_2D, ret_tex.image);

		if(ret_tex.components == 3)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ret_tex.width, ret_tex.height, 0, GL_RGB, GL_UNSIGNED_BYTE, data.data());
		else if(ret_tex.components == 4)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ret_tex.width, ret_tex.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.data());
		
		texture_map[texture_path] = ret_tex;
		return ret_tex;
	}

	gui::Texture* GUITextureFactory::TryFindInMap( const std::string& texture_path )
	{
		std::map<std::string, Texture>::iterator it = texture_map.find(texture_path);
		if(it != texture_map.end())
			return &it->second;
		else
			return NULL;
	}

}

