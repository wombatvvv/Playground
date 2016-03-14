#version 330 core

// Input vertex data, different for all exuctions of this shader
layout(location = 0) in vec3 vertexPosition_modelspace;

uniform mat4 ModelViewProjectionMatrix;

void main() {	
	// gl_Position.xyz = vertexPosition_modelspace;
	// gl_Position.w = 1.0;

 	// Multiply our matrix with the verticy to get the verticy's new position!
	gl_Position = ModelViewProjectionMatrix * vec4(vertexPosition_modelspace, 1);
}
