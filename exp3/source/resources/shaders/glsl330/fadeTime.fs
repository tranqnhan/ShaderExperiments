#version 330

#define FPS 60.0
#define MAX_FADE_STIME 8.0
#define MAX_FADE_FTIME int(FPS * MAX_FADE_STIME) // uint(FPS * MAX_FADE_STIME)

in vec2 fragTexCoord;
out vec4 fragColor;

uniform sampler2D iTexture;
uniform sampler2D iFadeTime;

void main()
{   
	vec4 source = texture(iTexture, fragTexCoord);
	vec4 fadeTimeColor = texture(iFadeTime, fragTexCoord);

  fadeTimeColor *= 255.0;

  uint fadeTimeI = uint(fadeTimeColor.r) | 
    (uint(fadeTimeColor.b) << 8) |
    (uint(fadeTimeColor.g) << 16) |
    (uint(fadeTimeColor.a) << 24);
  
  source.a = floor(source.a);

  fadeTimeI = 
    uint(uint(source.a * MAX_FADE_FTIME) + 
    uint(1.0 - source.a) * uint(fadeTimeI - min(2u, fadeTimeI)));

  fragColor.r = float(fadeTimeI & 0xFFu);
  fragColor.b = float((fadeTimeI & 0xFF00u) >> 8);
  fragColor.g = float((fadeTimeI & 0xFF0000u) >> 16); 
  fragColor.a = float((fadeTimeI & 0xFF000000u) >> 24); 
  fragColor /= 255.0;
  
}