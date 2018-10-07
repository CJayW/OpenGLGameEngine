#include "Light.h"


std::vector<DirectionalLight*> Light::directionalLights;
std::vector<PointLight*> Light::pointLights;
std::vector<SpotLight*> Light::spotLights;

Light::Light()
{
}


Light::~Light()
{
}