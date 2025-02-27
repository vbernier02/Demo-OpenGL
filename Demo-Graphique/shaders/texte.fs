#version 330
in vec4 mpos;
in vec3 mnormal;
in vec2 tcoord;
out vec4 fragColor;

uniform vec4 couleur;
uniform sampler2D tex;
uniform int use_tex;

void main() {
    vec4 c = texture(tex, tcoord);
    if(length(c.rgb) > 0.01)
        fragColor = c;
    else
        discard;
}		
