#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#ifdef _WIN32
#define NOMINMAX
#include <Windows.h>
#endif

#include <memory>

#include <GL/glew.h>
#include <SDL.h>
#include <glm/glm.hpp>

#include "Timer.h"
#include "GLUtils/GLUtils.hpp"
#include "Model.h"
#include "VirtualTrackball.h"
#include "ShadowFBO.h"
#include "SliderWithText.h"

#include "Game_Constants.h"
/**
 * This class handles the game logic and display.
 * Uses SDL as the display manager, and glm for 
 * vector and matrix computations
 */
class GameManager {
public:

	/**
	 * Constructor
	 */
	GameManager();

	/**
	 * Destructor
	 */
	~GameManager();

	/**
	 * Initializes the game, including the OpenGL context
	 * and data required
	 */
	void init();

	/**
	 * The main loop of the game. Runs the SDL main loop
	 */
	void play();

	/**
	 * Quit function
	 */
	void quit();

	/**
	 * Function that handles rendering into the OpenGL context
	 */
	void render();

	/**
	  * Function that renders a shadow pass
	  */
	void renderShadowPass();

	/**
	  * Function that renders to screen
	  */
	void renderColorPass();


	/**
	* Renders the light point of view as a depth representation 
	* to a square in the bottom left screen
	*/
	void renderDepthDump();

protected:
	/**
	 * Creates the OpenGL context using SDL
	 */
	void createOpenGLContext();

	
	static const unsigned int n_models = 20;

	static const float near_plane;
	static const float far_plane;
	static const float fovy;
	static const float cube_scale;
	
	static const float cube_vertices_data[];
	static const float cube_normals_data[];

private:
	void zoomIn();
	void zoomOut();
	
	void SetMatrices();
	void CreateShaderPrograms();
	void SetShaderUniforms();
	void SetShaderAttribPtrs();

	void RenderGUI();

	GLuint vao[2]; //< Vertex array objects
	std::shared_ptr<GLUtils::Program> phong_program,
									  wireframe_program,
									  hidden_line_program,
									  exploded_view_program, 
									  shadow_program,
									  depth_dump_program,
									  gui_program;

	std::shared_ptr<GLUtils::Program> current_program;

	std::shared_ptr<GLUtils::CubeMap> diffuse_cubemap;
	
	std::shared_ptr<GLUtils::BO<GL_ARRAY_BUFFER> > cube_vertices, cube_normals;

	std::shared_ptr<Model> model;
	std::shared_ptr<ShadowFBO> shadow_fbo;
	std::shared_ptr<ShadowFBO> screen_dump_fbo;

	std::shared_ptr<SliderWithText> slider_increase_line_width;

	GLuint fbo_vertex_bo; //< Vetex buffer object for fullscreen quad
	GLuint fbo_vao; //< Vertex array object for the depthbuffer dumping
	glm::mat4 fbo_modelMatrix;
	glm::mat4 fbo_projectionMatrix;
	glm::mat4 fbo_viewMatrix;

	Timer my_timer; //< Timer for machine independent motion
	float zoom; //< Zoom factor

	struct {
		glm::vec3 position; //< Light position for shading etc
		glm::mat4 projection;
		glm::mat4 view;
	} light;

	struct Camera{
		glm::mat4 projection;
		glm::mat4 view;
	};
	Camera camera;
	Camera gui_camera;
	std::vector<glm::mat4> model_matrices; //< OpenGL model transformation matrix
	std::vector<glm::vec3> model_colors;

	SDL_Window* main_window; //< Our window handle
	SDL_GLContext main_context; //< Our opengl context handle 
	
	VirtualTrackball cam_trackball;

	bool render_depth_dump;

	float delta_time;

};

#endif // _GAMEMANAGER_H_
