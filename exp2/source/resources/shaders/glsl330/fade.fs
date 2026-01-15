#version 330


in vec2 fragTexCoord;
out vec4 fragColor;

uniform sampler2D iTexture;

void main()
{   
	vec4 source = texture(iTexture, fragTexCoord);
	fragColor.rgb = source.rgb; 
	fragColor.a = source.a - (1.0 / 255.0);
}