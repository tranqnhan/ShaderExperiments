#version 330

#define FPS 60.0
#define MAX_FADE_STIME 8.0
#define MAX_FADE_FTIME int(FPS * MAX_FADE_STIME)

in vec2 fragTexCoord;
out vec4 fragColor;

uniform sampler2D iTexture;
uniform sampler2D iFadeTime;


void main()
{   
	vec4 source = texture(iTexture, fragTexCoord);
	fragColor.rgb = source.rgb; 

	vec4 fadeTime = texture(iFadeTime, fragTexCoord) * 255;


	int fadeTimeI = int(fadeTime.a) | 
		(int(fadeTime.b) << 8) |
		(int(fadeTime.g) << 16) |
		(int(fadeTime.r) << 24);


	fragColor.a = fadeTimeI / float(MAX_FADE_FTIME);
}