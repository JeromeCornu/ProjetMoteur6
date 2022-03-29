#version 330 core

layout(location = 0) in vec3 VertexPosition_modelspace;
layout(location = 1) in vec2 VertexUV;
layout(location = 2) in vec3 Normals;

// SKY
layout (location = 3) in vec3 aPosSky;

out vec3 TexCoordsSky;

uniform mat4 projectionSky;
uniform mat4 viewSky;
// ---


vec4 gl_Position;

vec3 Position_worldspace;
vec3 EyeDirection_cameraspace;

// out vec3 fragmentColor;
out vec2 UV;
out vec3 Normal_cameraspace;
out vec3 LightDirection_cameraspace;
out float DistanceLightVertex;

uniform mat4 MVP;	// Model View Projection
uniform mat4 Model; // matrice sur laquelle on s'appuie pour nos constructions
uniform mat4 View;	// camera matrice
uniform vec3 LightPosition_worldspace;


void main()
{
	// SKY
  TexCoordsSky = aPosSky;
  // gl_Position = projectionSky * viewSky * vec4(aPosSky, 1.0);
	// ---

  gl_Position =  MVP * vec4(VertexPosition_modelspace,1);
  UV = VertexUV;

  Position_worldspace = (Model * vec4(VertexPosition_modelspace,1)).xyz;
 
  vec3 VertexPosition_cameraspace = ( View * Model * vec4(VertexPosition_modelspace,1)).xyz;	// sommet - vertex ref de l'objet "camera" utilis� pour changer d'espace
  EyeDirection_cameraspace = vec3(0,0,0) - VertexPosition_cameraspace;


  vec3 LightPosition_cameraspace = ( View * vec4(LightPosition_worldspace,1)).xyz;
  LightDirection_cameraspace = LightPosition_cameraspace + EyeDirection_cameraspace;
  

  DistanceLightVertex = distance(VertexPosition_cameraspace, LightPosition_cameraspace);

  // Only correct if ModelMatrix does not scale the model ! Use its inverse transpose if not.
  Normal_cameraspace = ( View * Model * vec4(Normals,0)).xyz;

}