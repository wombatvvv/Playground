// Standard Headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// Using the GLEW library
#include <glew.h>


// Lets GLFW handle the keyboard and window
#include <glfw3.h>

// Declares a global GLFW window
GLFWwindow* window;

// This is a library for 3D mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <UtilsFromTutorials/shader.hpp>



using namespace glm;

static const std::string VERTEX_SHADER_PATH = "../src/shaders/SimpleVertexShader.glsl";
static const std::string FRAGMENT_SHADER_PATH = "../src/shaders/SimpleFragmentShader.glsl";

bool shouldNotCloseWindow();

int main( void )
{	
	// Initialise GLFW	
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4); // Set 4X anti-aliasing
	
	// Set OpenGL version to 3.3
	glfwWindowHint(GLFW_RESIZABLE,GL_FALSE); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Don't want the old OpenGL (?)

	// Open a window and create its OpenGL context
	// This variable is declared globally at the top of the code.
	window = glfwCreateWindow( 1000, 768, "Playground", NULL, NULL);
	
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(window); // (?)
	glewExperimental = true; // Needed in core profile (?)

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Creates a Vertex Array Object (VAO)
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);

	// Sets the VAO created above to the current one.
	glBindVertexArray(VertexArrayID);

	GLuint programID = LoadShaders(VERTEX_SHADER_PATH.c_str(), FRAGMENT_SHADER_PATH.c_str());

	// Indetify the variable in GLSL that will hold our ModelViewProjection Matrix.
	GLuint ModelViewProjectionMatrixID = glGetUniformLocation(programID, "ModelViewProjectionMatrix");
	
	// --- Applying the Model-View-Projection matrix ---------------------------------------------------
	// The MVP matrix is a matrix resulting in the multiplication of varies matricies that will be used
	// to by GLSL to move the matricies in the world around so that the resulting scene being rendered
	// looks as though it comes from a certain perspective (i.e. a certain position in space, with a certain
	// "projection" (i.e. "camera lens").

	// Projection Matrix
	// -----------------
	float radians = 45.0f;
	float screenRatio = 4.0f / 3.0f; // e.g. 800x600, 1280x960
	float nearClippingPlane = 0.1f; // (?) Keep it as big as possible apparently.
	float farClippingPlane = 100.0f; // (?) Keep it as small as possible apparently.

	glm::mat4 ProjectionMatrix = glm::perspective(	radians, 
													screenRatio, 
													nearClippingPlane, 
													farClippingPlane);
	// Or, for an ortho camera :
	//glm::mat4 ProjectionMatrix = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates



	// View Matrix
	// -----------
	glm::vec3 positionInWorldSpace = glm::vec3(4, 3, 3);
	glm::vec3 pointToLookAt = glm::vec3(0, 0, 0); // look at the origin
	glm::vec3 headIsUp = glm::vec3(0, 1, 0); // (0, -1, 0) and we're looking at everything upside down.

	glm::mat4 ViewMatrix = glm::lookAt(positionInWorldSpace, pointToLookAt, headIsUp);


	// Model Matrix
	// ------------
	glm::mat4 ModelMatrix = glm::mat4(1.0f); // (?)


	// Complete ModelViewProjectionMatrix
	// ----------------------------------
	// Note: remember, these multiplactions are done in reverse order: model, then view, then projection.
	glm::mat4 ModelViewProjectionMatrix = ProjectionMatrix * ViewMatrix * ModelMatrix;




	static const GLfloat g_vertex_buffer_data[] = {
		// static	- in this context means this variable will "stick around' in memory unil the program completey ends.
		//			- this means it will only ever be initialised once (even in the case it is initialised in a loop).
		// const	- the value will and can never change.
       -1.0f, -1.0f, 0.0f, // vertex 1: (XYZ), indicates that far left, far bottom of the screen.
		1.0f, -1.0f, 0.0f, // vertex 2: The far right, far bottom of the screen.
		0.0f,  1.0f, 0.0f, // vertex 3: the center, far top of the screen.
	};
	

	// Now we need to "give' this definition to OpenGL. We do this by creating a buffer:
	GLuint vertexbuffer; // used to identify our buffer.
	glGenBuffers(1, &vertexbuffer); // Generate 1 buffer & put the resulting identifier into vertexbuffer.
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer); // bind the vertex buffer defined by identifier in vertexbuffer (?).
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW); // (?)																							   // This will create and complile the GSLS program from the shader code which I believe is run on
																									   // the graphics hardware.
	// Set the clear-screen colour.
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	do {				
		glClear(GL_COLOR_BUFFER_BIT); // Clear the screen		
		
		glUseProgram(programID);

		// Send our ModelViewProjection Matrix to the currently bound shader
		// setting it as ModelViewProjectionMatrix in the GLSL code.
		glUniformMatrix4fv(
			ModelViewProjectionMatrixID, // The ID to use, defined above.
			1,
			GL_FALSE,
			&ModelViewProjectionMatrix[0][0] // A reference the ModelViewProjectionMatrix - [0][0] (?)
			);		

		glEnableVertexAttribArray(0); // (?)
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		
		// I believe these values correspond to values in the shader, and this line is basically
		// passing data over to the hardware (???).
		glVertexAttribPointer(
			0,			// Attrib 0: No reason for 0, but must match the layout in the shader.
			3,			// Attrib 1 (?): size (number of verticies).
			GL_FLOAT,	// Attrib 2 (?): type definition of verticies.
			GL_FALSE,	// Attrib 3 (?): normalized? (?)
			0,			// Attrib 4 (?): stride (?)
			(void*)0	// Attrib 5 (?): array buffer offset (?)
			);

		// Draw the verticies...
		glDrawArrays(
			GL_TRIANGLES, // I think this is saying to draw triangle polygons... (?)
			0,	// starting at vertex no. 0.
			3	// total number of verticies to draw.
			);

		glDisableVertexAttribArray(0); // (?)

		glfwSwapBuffers(window);
		glfwPollEvents();
	} while (shouldNotCloseWindow());

}

bool shouldNotCloseWindow() {
	bool isNoNeedToCloseWindow = glfwWindowShouldClose(window) == 0;
	bool escapeKeyIsUnpressed = glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS;
	return isNoNeedToCloseWindow && escapeKeyIsUnpressed;
}

