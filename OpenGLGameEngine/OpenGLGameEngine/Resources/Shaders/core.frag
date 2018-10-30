#version 330 core
out vec4 FragColor;


struct DirLight {
    vec3 direction;
  
    vec3 diffuse;
};

struct PointLight {    
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;  

    vec3 diffuse;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 diffuse;
};

#define MaxLightCount 10  

uniform DirLight dirLights[MaxLightCount];
uniform PointLight pointLights[MaxLightCount];
uniform SpotLight spotLights[MaxLightCount];

uniform vec3 Ambient;

vec3 CalcDirLight(DirLight light, vec3 normal);  
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos);  
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos);

in vec3 Color;
in vec3 Normal;
in vec3 FragPos;

void main()
{
	vec3 norm = normalize(Normal);

	vec3 result = Color * Ambient;

    // phase 1: Directional lighting
	for(int i = 0; i < MaxLightCount; i++) {
		if(dirLights[i].diffuse != vec3(0)){
			 result += CalcDirLight(dirLights[i], norm);

		}else{
			break;
			//TODO this will not render lights. Check the comment in Light.h
		}
	}
	// phase 2: Point lights
    for(int i = 0; i < MaxLightCount; i++) {
		if(pointLights[i].diffuse != vec3(0)){
			 result += CalcPointLight(pointLights[i], norm, FragPos);  
		}else{
			break;
		}
	}

    // phase 3: Spot light
	for(int i = 0; i < MaxLightCount; i++) {
		if(spotLights[i].diffuse != vec3(0)){
			result += CalcSpotLight(spotLights[i], norm, FragPos);
		}else{
			break;
		}

	}
    FragColor = vec4(result, 1.0);
}

vec3 CalcDirLight(DirLight light, vec3 normal){
	vec3 lightDir = normalize(-light.direction);

	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);

	// combine results
	vec3 diffuse  = light.diffuse  * diff * Color;

	return (diffuse);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos){
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
  			     light.quadratic * (distance * distance));    
    // combine results
    vec3 diffuse  = light.diffuse  * diff * Color;
   // ambient *= attenuation;
    diffuse *= attenuation;

    return (diffuse);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 diffuse = light.diffuse * diff * Color;
    diffuse *= attenuation * intensity;
    
	return (diffuse);
}
