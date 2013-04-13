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
	void createOpenGLContext();

	static const unsigned int number_of_models = 20;

	static const float near_plane;
	static const float far_plane;
	static const float fovy;
	static const float cube_scale;
	
	static const float cube_vertices_data[];
	static const float cube_normals_data[];
	
	static GLuint gui_vbo, gui_vao;

private:
	/**
	* Vertex array objects
	* vao[0] == vao for bunnies
	* vao[1] == vao for room-cube
	* vao[2] == vao for modelled room
	* vao[3] == vao for fbo
	*/
	GLuint vao[4];

	std::shared_ptr<GLUtils::Program> phong_program,
									  wireframe_program,
									  hidden_line_program,
									  exploded_view_program, 
									  light_pov_program,
									  depth_dump_program,
									  gui_program;

	// Pointer to the program currently used for the color pass scene drawing
	std::shared_ptr<GLUtils::Program> current_program; 

	std::shared_ptr<CubeMap> diffuse_cubemap; //< Cubemap with the scenes diffuse light
	std::shared_ptr<CubeMap> spacebox;		  //< Cubemap for the spacebox surrounding the scene

	std::shared_ptr<GLUtils::BO<GL_ARRAY_BUFFER> > cube_vertices, cube_normals, gui_vertices;

	std::shared_ptr<Model> bunny;
	std::shared_ptr<Model> room;

	std::shared_ptr<ShadowFBO> shadow_fbo;

	std::shared_ptr<gui::SliderWithText> slider_line_threshold; //< GUI slider modifying the hidden-line wireframe line tickness
	std::shared_ptr<gui::SliderWithText> slider_line_scale;		//< GUI slider modifying the hidden-line wireframe line fade scale
	std::shared_ptr<gui::SliderWithText> slider_line_offset;	//< GUI slider modifying the hidden-line wireframe line fade out
	std::shared_ptr<gui::SliderWithText> slider_diffuse_mix;	//< GUI slider modifying the way the diffuse color is mixed in phong shaders
	std::shared_ptr<gui::SliderWithText> slider_gui_alpha;		//< GUI slider modifying the alpha of all gui objects
	std::vector<std::shared_ptr<gui::SliderWithText>> gui_sliders; //< Collection of the sliders
	
	std::shared_ptr<gui::RadioButtonCollection> rendermode_radiobtn;
	std::shared_ptr<gui::RadioButtonCollection> environment_radiobtn;

	GLuint fbo_vertex_bo; //< Vetex buffer object for fullscreen quad

	glm::mat4 cam_trackball_view_matrix;

	// Matrices for the depth-dumping quad
	glm::mat4 fbo_modelMatrix;		
	glm::mat4 fbo_projectionMatrix;
	glm::mat4 fbo_viewMatrix;

	glm::mat4 room_model_matrix; //< Model matrix for the modelled room
	glm::mat4 room_model_matrix_inverse; //< inverse of above matrix
	glm::mat4 cube_model_matrix; //< Model matrix for the cube room
	glm::mat4 cube_model_matrix_inverse;//< inverse of above matrix

	std::vector<glm::mat4> model_matrices; //< Model transformationmatrices for each bunny
	std::vector<glm::mat4> model_inverse_matrices; //<Model inverse transformation matrices for each bunny
	std::vector<glm::vec3> model_colors;   //< Colors for each bunny

	Timer my_timer;		//< Timer for machine independent motion
	float delta_time;	//< Program Delta-time variable
	float zoom;			//< Zoom factor
	
	bool render_gui_and_depth;
	bool rotate_light;

	/**
	* Enum representation of the different environments we can 
	* use in the program. The current_environment variable holds
	* the one active at this point in time.
	*/ 
	enum Environements{
		PLAIN_CUBE_ROOM,
		OPEN_HALFROOM
	}current_environment;

	/**
	* Struct for the light position and the projection and view matrices.
	*/
	struct {
		glm::vec3 position;
		glm::mat4 projection;
		glm::mat4 view;
	} light;

	/**
	* Struct with a cameras projection and view matrices
	*/
	struct Camera{
		glm::mat4 projection;
		glm::mat4 view;
	}camera, gui_camera;


	SDL_Window* main_window; //< Our window handle
	SDL_GLContext main_context; //< Our opengl context handle 
	
	VirtualTrackball cam_trackball;

	void zoomIn();
	void zoomOut();

	void Init_SetMatrices();
	void Init_CreateShaderPrograms();
	void Init_SetShaderUniforms();
	void Init_SetShaderAttribPtrs();
	void Init_set_vao_0_attribPtrs(); //< Attrib ptrs for the bunnies vao
	void Init_set_vao_1_attribPtrs(); //< Attrib ptrs for the cube room vao
	void Init_set_vao_2_attribPtrs(); //< Attrib ptrs for the half open room vao
	void Init_set_vao_3_attribPtrs(); //< Attrib ptrs for the FBO vao
	void Init_CreateGUIObjects();

	void RenderGUI();
	void RenderCubeColorpass();
	void RenderCubeShadowpass();

	void RenderModelsColorpass();
	void RenderModelsShadowpass();

	void RenderRoomModelColorpass();
	void RenderRooomModelShadowpass();

/************************************************************************/
/* The functions below are used for callbacks to the GUI classes        */
/************************************************************************/
	
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
	* Sets the current room environemnt to be rendered to the cube room
	*/
	void SetBackgroundToCube();

	/**
	* Sets the current room environemnt to be rendered to the half open room
	*/
	void SetBackgroundToOpenRoom();
};

#endif // _GAMEMANAGER_H_
