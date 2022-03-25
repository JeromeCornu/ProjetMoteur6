#version 330 core

//in vec3 fragmentColor;
out vec3 Color;

in vec2 UV;
in vec3 Normal;
in vec3 Normal_cameraspace;
in vec3 LightDirection_cameraspace;
in float DistanceLightVertex;

uniform sampler2D MyTextureSampler;

vec3 MaterialDiffuseColor = vec3 (1.0f, 1.0f, 1.0f);

// Light
vec3 LightColor = vec3 (1.0f, 1.0f, 1.0f);
float LightPower = 20.0f;
vec3 PointLight;

// Ambient Light 
float AmbientStrength = 0.1;
vec3 AmbientColor = vec3 (1.0f, 1.0f, 1.0f);


void main()
{

  // ---------------  Light  --------------------

  // Normal of the computed fragment, in camera space
  vec3 N = normalize( Normal_cameraspace );

  // Direction of the light (from the fragment to the light)
  vec3 L = normalize( LightDirection_cameraspace );

  // Cosine of the angle between the normal and the light direction
  float CosTheta = clamp( dot( Normal_cameraspace, LightDirection_cameraspace ), 0, 1);	// dot( n,l ) = n.l -- clamp -> return the hightest number

  PointLight = MaterialDiffuseColor * texture( MyTextureSampler, UV ).rgb*(max(CosTheta, 0.1)) * LightPower * LightColor / (DistanceLightVertex * DistanceLightVertex);
  
  // -----------  Ambient Light  ----------------
  
  vec3 Ambient = AmbientColor * AmbientStrength * MaterialDiffuseColor * texture( MyTextureSampler, UV ).rgb*(max(CosTheta, 0.1));

  Color = max(Ambient, PointLight);

}