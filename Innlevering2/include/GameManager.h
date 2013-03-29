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
#include "CubeMap.h"
#include "RadioButtonCollection.h"
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
	void CreateGUIObjects();

	void RenderGUI();

	glm::mat4 view_matrix_new;
	void RenderCubeColorpass();
	void RenderCubeShadowpass();

	void RenderModelsColorpass();
	void RenderModelsShadowpass();

	void RenderRoomModelColorpass();
	void RenderRooomModelShadowpass();


	static GLuint gui_vbo, gui_vao;
	
	GLuint vao[3]; //< Vertex array objects
	std::shared_ptr<GLUtils::Program> phong_program,
									  wireframe_program,
									  hidden_line_program,
									  exploded_view_program, 
									  light_pov_program,
									  depth_dump_program,
									  gui_program,
									  frensel_program;

	std::shared_ptr<GLUtils::Program> current_program;

	std::shared_ptr<CubeMap> diffuse_cubemap;
	std::shared_ptr<CubeMap> spacebox;

	std::shared_ptr<GLUtils::BO<GL_ARRAY_BUFFER> > cube_vertices, cube_normals, gui_vertices;

	std::shared_ptr<Model> bunny;
	std::shared_ptr<Model> room;

	std::shared_ptr<ShadowFBO> shadow_fbo;
	std::shared_ptr<ShadowFBO> screen_dump_fbo;

	std::shared_ptr<SliderWithText> slider_line_threshold;
	std::shared_ptr<SliderWithText> slider_line_scale;
	std::shared_ptr<SliderWithText> slider_line_offset;

	std::shared_ptr<SliderWithText> slider_shadefactor_addvalue;
	std::shared_ptr<SliderWithText> slider_shadefactor_multiplier;
		
	std::shared_ptr<RadioButtonCollection> rendermode_radiobtn;
	std::shared_ptr<RadioButtonCollection> environment_radiobtn;
	GLuint fbo_vertex_bo; //< Vetex buffer object for fullscreen quad
	GLuint fbo_vao; //< Vertex array object for the depthbuffer dumping
	glm::mat4 fbo_modelMatrix;
	glm::mat4 fbo_projectionMatrix;
	glm::mat4 fbo_viewMatrix;

	glm::mat4 room_model_matrix;
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

	bool render_gui_and_depth;
	bool rotate_light;

	float delta_time;

	/**
	* Switch to the phong shading program
	*/
	void UsePhongProgram();
	/**
	* Switch to the wireframe shading program
	*/
	void UseWireframeProgram();
	/**
	* Switch to the hidden line shading program
	*/
	void UseHiddenLineProgram();
	/**
	* Switch to the frensel shading program
	*/
	void UseFrenselProgram();

	void SetBackgroundToCube();
	void SetBackgroundToOpenRoom();

	enum Environements{
		PLAIN_CUBE_ROOM,
		OPEN_HALFROOM
	};
	Environements current_environment;
};

#endif // _GAMEMANAGER_H_
