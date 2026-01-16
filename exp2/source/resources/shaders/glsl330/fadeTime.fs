#version 330

#define FPS 300.0
#define MAX_FADE_STIME 8.0
#define MAX_FADE_FTIME uint(FPS * MAX_FADE_STIME)

in vec2 fragTexCoord;
out vec4 fragColor;

uniform sampler2D iTexture;
uniform sampler2D iFadeTime;


void main()
{   
	vec4 source = texture(iTexture, fragTexCoord);
  
  

  if (source.a >= 1.0) {

    fragColor.a = 0;
    fragColor *= 255;
    uint fadeTimeI = uint(fragColor.r) | 
      (uint(fragColor.b) << 8) |
      (uint(fragColor.g) << 16) |
      (uint(fragColor.a) << 24);

    fadeTimeI = MAX_FADE_FTIME;
  
    fragColor.r = float(fadeTimeI & 0xFFu);
    fragColor.b = float((fadeTimeI & 0xFF00u) >> 8);
    fragColor.g = float((fadeTimeI & 0xFF0000u) >> 16); 
    fragColor.a = float((fadeTimeI & 0xFF000000u) >> 24); 

    fragColor.a = 255;
    fragColor /= 255.0;
  } else {
    //if (fadeTimeI > 0u) {
     // fadeTimeI = fadeTimeI - 1u;
   // }
  }


}