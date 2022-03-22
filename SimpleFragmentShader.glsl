#version 330 core

//in vec3 fragmentColor;
out vec3 color;

in vec2 UV;
in vec3 normal;
in vec3 Normal_cameraspace;
in vec3 LightDirection_cameraspace;
in float distanceLightVertex;

uniform sampler2D myTextureSampler;

vec3 MaterialDiffuseColor = vec3 (1.0f, 1.0f, 1.0f);

// Light
vec3 lightColor = vec3 (1.0f, 1.0f, 1.0f);
float LightPower = 20.0f;
vec3 pointLight;

// Ambient Light 
float ambientStrength = 0.1;
vec3 ambientColor = vec3 (1.0f, 1.0f, 1.0f);


void main()
{

  // ---------------  Light  --------------------

  // Normal of the computed fragment, in camera space
  vec3 n = normalize( Normal_cameraspace );

  // Direction of the light (from the fragment to the light)
  vec3 l = normalize( LightDirection_cameraspace );

  // Cosine of the angle between the normal and the light direction
  float cosTheta = clamp( dot( Normal_cameraspace, LightDirection_cameraspace ), 0, 1);	// dot( n,l ) = n.l -- clamp -> return the hightest number

  pointLight = MaterialDiffuseColor * texture( myTextureSampler, UV ).rgb*(max(cosTheta, 0.1)) * LightPower * lightColor / (distanceLightVertex * distanceLightVertex);
  
  // -----------  Ambient Light  ----------------
  
  vec3 ambient = ambientColor * ambientStrength * MaterialDiffuseColor * texture( myTextureSampler, UV ).rgb*(max(cosTheta, 0.1));

  color = max(ambient, pointLight);

}