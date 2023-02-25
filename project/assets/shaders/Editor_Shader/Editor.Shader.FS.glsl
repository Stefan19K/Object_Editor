#version 330

in vec2 texcoord;

uniform sampler2D texture_1;
uniform sampler2D texture_2;
uniform int multipleTextures;

layout(location = 0) out vec4 out_color;


void main()
{
    vec4 color1 = texture2D(texture_1, texcoord); 
    vec4 color2 = texture2D(texture_2, texcoord); 
    
    if (multipleTextures == 0) {
        out_color = color1;
    } else {
        out_color = mix(color1, color2, 0.5f);
    }
}
