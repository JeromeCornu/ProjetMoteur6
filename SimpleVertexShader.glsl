#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 normals;


vec4 gl_Position;

vec3 Position_worldspace;
vec3 EyeDirection_cameraspace;

// out vec3 fragmentColor;
out vec2 UV;
out vec3 Normal_cameraspace;
out vec3 LightDirection_cameraspace;
out float distanceLightVertex;

uniform mat4 MVP;	// Model View Projection
uniform mat4 Model; // matrice sur laquelle on s'appuie pour nos constructions
uniform mat4 View;	// camera matrice
uniform vec3 LightPosition_worldspace;


void main()
{
  gl_Position =  MVP * vec4(vertexPosition_modelspace,1);
  UV = vertexUV;

  Position_worldspace = (Model * vec4(vertexPosition_modelspace,1)).xyz;
 
  vec3 vertexPosition_cameraspace = ( View * Model * vec4(vertexPosition_modelspace,1)).xyz;	// sommet - vertex ref de l'objet "camera" utilis� pour changer d'espace
  EyeDirection_cameraspace = vec3(0,0,0) - vertexPosition_cameraspace;


  vec3 LightPosition_cameraspace = ( View * vec4(LightPosition_worldspace,1)).xyz;
  LightDirection_cameraspace = LightPosition_cameraspace + EyeDirection_cameraspace;
  

  distanceLightVertex = distance(vertexPosition_cameraspace, LightPosition_cameraspace);

  // Only correct if ModelMatrix does not scale the model ! Use its inverse transpose if not.
  Normal_cameraspace = ( View * Model * vec4(normals,0)).xyz;

}