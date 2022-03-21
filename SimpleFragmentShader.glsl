#version 330 core

//in vec3 fragmentColor;
out vec3 color;

in vec2 UV;
in vec3 normal;
in vec3 Normal_cameraspace;
in vec3 LightDirection_cameraspace;
in float distanceLightVertex;

uniform sampler2D myTextureSampler;


// const vec3 light = normalize(vec3(0.2, 0.8, 1.0));

// vec3 MaterialDiffuseColor  = vec3 (0.0f, 0.0f, 0.0f);
float LightPower = 60.0f;



void main(){
  //color = vec3(1,0,0);
  //color = fragmentColor;


  // ---------------  Light  --------------------

  // Normal of the computed fragment, in camera space
  vec3 n = normalize( Normal_cameraspace );

  // Direction of the light (from the fragment to the light)
  vec3 l = normalize( LightDirection_cameraspace );

  // Cosine of the angle between the normal and the light direction
  float cosTheta = clamp( dot( Normal_cameraspace, LightDirection_cameraspace ), 0, 1);	// dot( n,l ) = n.l -- clamp -> return the hightest number

  color = texture( myTextureSampler, UV ).rgb*(max(cosTheta, 0.1)) * LightPower / (distanceLightVertex * distanceLightVertex);
  //color = MaterialDiffuseColor * light * LightPower * cosTheta / (distance * distance); 
  }