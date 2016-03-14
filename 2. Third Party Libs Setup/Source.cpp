// GLFW
/*
1. Generate the files I needed using CMake following the instructions found here: http://www.glfw.org/docs/latest/compile.html.
2. Use Visual Studio (or any other compiler) to compile the generated code.
3. Locate the necessary library file (glfw3.lib in this case), and move it to whatever directory needed for libraries.
		- in this case, I also renamed it "glfw3-32bit-lib" as that's the version I generated and compiled.
4. Locate the necessary header file (glfw3.h) in this case, and move it to whatever directory needed for 3rd-party headers.
5. Be sure to upsate the Project settings - the linker needs to have the directory set to locate both files, and the actual library file included.
		- Directory for headers, set in Properties -> C++ -> General -> Additional Include Directories
		- Directory for lib files, set in Properties -> Linker -> General -> Additional Library Directories
		- The actual library file name, set in Properties -> Linker -> Input -> Additional Dependencies
		NOTE: the are seperate configurations for 32/64bit and Release/Debug in the properties window. Be sure to be setting the right one.
6. Note the documentation mentioned that opengl32.lib is also needed for GLFW, so that was added in Additional Dependencies. I believe it's included
   in Windows by default.
*/

// GLEW
// To get GLEW working, I basically did the exact the same as above, only I copied the glew32d.dll file into the directory where the .exe file is run from.
// It could also go in Windows/System or wherever.

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

#include <glew.h>
#include <glfw3.h>

// This is a library for 3D mathematics. Nothing special was required. Just include the source files provided in the include directory.
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


using namespace std;

int main(void)
{
	//GLFWwindow* window;

	int glfwWorks = glfwInit();
	std::cout << "GLFW Works: " << (glfwWorks ? "true" : "false") << std::endl;

	GLenum glewWorks = (int)glewInit();
	std::cout << "GLEW Works: " << (glewWorks ? "true" : "false") << std::endl;

	cin.get();
	return 0;

}