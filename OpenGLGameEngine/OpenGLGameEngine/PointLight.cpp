#include "PointLight.h"

std::string PointLight::name = "PointLight";


PointLight::PointLight() {
	pointLights.push_back(this);

}

PointLight::PointLight(std::string params) {
	pointLights.push_back(this);

	ambient = glm::vec3(0);
	diffuse = glm::vec3(0.8f);

	constant = 1.0f;
	linear = 0.09f;
	quadratic = 0.032;
	//TODO implament a range to this
	//http://wiki.ogre3d.org/tiki-index.php?page=-Point+Light+Attenuation
}


PointLight::~PointLight() {
}