// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <iostream>
#include <vector>

#include "PlaneMesh.hpp"
#include "LoadShaders.hpp"
#include "textureLoader.hpp"
#include "TextureMesh.hpp"


//////////////////////////////////////////////////////////////////////////////
// Main
//////////////////////////////////////////////////////////////////////////////

int main( int argc, char* argv[])
{

	///////////////////////////////////////////////////////
	float screenW = 1500;
	float screenH = 1500;
	float stepsize = 1.0f;

	float xmin = -10;
	float xmax = 10;

	if (argc > 1 ) {
		screenW = atoi(argv[1]);
	}
	if (argc > 2) {
		screenH = atoi(argv[2]);
	}
	if (argc > 3) {
		stepsize = atof(argv[3]);
	}
	if (argc > 4) {
		xmin = atof(argv[4]);
	}
	if (argc > 5) {
		xmax = atof(argv[5]);
	}


	///////////////////////////////////////////////////////

	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // For macOS
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow( screenW, screenH, "Phong", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	GLuint shaderProgram = LoadShaders(
		"WaterShader.vertexshader",
		"WaterShader.fragmentshader",
		"WaterShader.tcs",
		"WaterShader.tes",
		"WaterShader.geoshader"
	);	

	PlaneMesh plane(xmin, xmax, stepsize);
	
	GLuint textureShader = LoadShaders("TextureShader.vertexshader", "TextureShader.fragmentshader");
	TextureMesh boat("Assets/boat.ply", "Assets/boat.bmp", textureShader);
	TextureMesh head("Assets/head.ply", "Assets/head.bmp", textureShader);
	TextureMesh eyes("Assets/eyes.ply", "Assets/eyes.bmp", textureShader);


	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.2f, 0.2f, 0.3f, 0.0f);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glDisable(GL_CULL_FACE);

	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), screenW/screenH, 0.001f, 1000.0f);

	glm::mat4 V;

	glm::vec3 lightpos(5.0f, 30.0f, 5.0f);
	glm::vec4 color1(1.0f, 1.0f, 1.0f, 1.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	GLuint waterTextureID = loadBMP_custom("Assets/water.bmp");
	GLuint displacementTextureID = loadBMP_custom("Assets/displacement-map1.bmp");

	do{
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// cameraControlsGlobe(V, 5);
		glm::vec3 eye = glm::vec3(0, 10, 20);
		glm::vec3 center = glm::vec3(0, 0, 0);
		glm::vec3 up = glm::vec3(0, 1, 0);
		V = glm::lookAt(eye, center, up);
		glm::mat4 M = glm::mat4(1.0f); // model matrix
    	glm::mat4 MVP = Projection * V * M;
		
		float t = glfwGetTime();

		glUseProgram(shaderProgram); // Make sure your shader is bound!

		GLuint textureShader = LoadShaders("TextureShader.vertexshader", "TextureShader.fragmentshader");
		std::cout << "[INIT] Texture shader program ID: " << textureShader << std::endl;


		// Set matrix uniforms
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "MVP"), 1, GL_FALSE, glm::value_ptr(MVP));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "M"), 1, GL_FALSE, glm::value_ptr(M));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "V"), 1, GL_FALSE, glm::value_ptr(V));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "P"), 1, GL_FALSE, glm::value_ptr(Projection));

		// Set camera & light positions
		glUniform3fv(glGetUniformLocation(shaderProgram, "eyePos"), 1, glm::value_ptr(glm::vec3(0, 10, 20)));
		glUniform3fv(glGetUniformLocation(shaderProgram, "lightPos"), 1, glm::value_ptr(lightpos));

		// Set time and color
		glUniform1f(glGetUniformLocation(shaderProgram, "time"), t);
		glUniform4f(glGetUniformLocation(shaderProgram, "modelcolor"), 0.0f, 1.0f, 1.0f, 1.0f);

		// Set tessellation levels (if you're using uniforms for this)
		glUniform1f(glGetUniformLocation(shaderProgram, "outerTess"), 16.0f);
		glUniform1f(glGetUniformLocation(shaderProgram, "innerTess"), 16.0f);

		// Bind textures
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, waterTextureID); // Make sure you loaded this
		glUniform1i(glGetUniformLocation(shaderProgram, "modelTexture"), 0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, displacementTextureID); // Also needs to be loaded
		glUniform1i(glGetUniformLocation(shaderProgram, "displacementTexture"), 1);

		// Set patch type before draw
		glPatchParameteri(GL_PATCH_VERTICES, 4);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		// Draw the plane
		plane.draw();

		// Transform for boat (optional: float up/down based on wave later)
		glm::mat4 boatModel = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0.5f, 0));
		boat.draw(lightpos, V, Projection, boatModel);

		// Head on a different spot
		glm::mat4 headModel = glm::translate(glm::mat4(1.0f), glm::vec3(-3, 0.5f, 2));
		head.draw(lightpos, V, Projection, headModel);

		// Eyes above head
		glm::mat4 eyesModel = glm::translate(glm::mat4(1.0f), glm::vec3(-3, 1.0f, 2));
		eyes.draw(lightpos, V, Projection, eyesModel);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Close OpenGL window and terminate GLFW
	glfwTerminate();
	return 0;
}

