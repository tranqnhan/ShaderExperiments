#version 330


in vec2 fragTexCoord;
out vec4 fragColor;

uniform int iTime;
uniform sampler2D iTexture;

void main()
{    
    //vec2 uv = fragTexCoord.xy / iResolution.xy;
    float sinEffect = (sin(iTime * (1/60.0)) + 1) / 2.0;
    vec4 source = texture(iTexture, fragTexCoord);


    fragColor.r = sinEffect;
	fragColor.g = sinEffect;
	fragColor.b = source.b;
	fragColor.a = source.a;


}