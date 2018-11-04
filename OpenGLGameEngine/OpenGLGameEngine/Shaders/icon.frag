#version 330 core
out vec4 FragColor;


in vec3 FragPos;
in vec2 TexCoord;

uniform sampler2D Texture;

void main()
{
	vec4 col = texture(Texture, TexCoord);

	if(col.x < 0.6){
		discard;
	}

	FragColor = col;
}