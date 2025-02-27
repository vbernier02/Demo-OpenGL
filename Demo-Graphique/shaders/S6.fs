#version 330

in vec4 mpos;
in vec3 mnormal;
in vec2 tcoord;
in vec4 smcoord;
out vec4 fragColor;

uniform vec4 couleur;
uniform vec4 lumpos0;
uniform vec4 lumpos1;
uniform vec4 lumpos2;
uniform vec4 lumpos3;
uniform vec4 lumpos4;
uniform vec4 lumpos5;
uniform vec4 lumpos6;
uniform mat4 view;
uniform sampler2D tex;
uniform sampler2D nm;
uniform sampler2D sm;
uniform int use_tex;
uniform int use_nm;

void main() {
    const vec3 V = vec3(0.0, 0.0, -1.0);
    const vec4 acouleur = vec4(0.0, 0.3, 0.0, 1.0);
    vec3 Ld0 = normalize(lumpos0.xyz - mpos.xyz);
    vec3 N = mnormal;
    if(use_nm == 1) {
        vec2 p = (texture(nm, tcoord).rb - vec2(0.5)) * 2.0;
        N = normalize(N + 0.5 * vec3(-p.x, 0.0, p.y));
    }

    vec3 smpcoord = smcoord.xyz / smcoord.w;
    float ild0 = clamp(dot(N, Ld0), 0.0, 1.0);
    float z = texture(sm, smpcoord.xy).r;
    if(z < smpcoord.z)
        ild0 = 0.0;
    
    vec3 R0 = reflect(Ld0, N);
    R0 = normalize((transpose(inverse(view)) * vec4(R0, 0.0)).xyz);
    float ils0 = pow(clamp(dot(R0, -V), 0.0, 1.0), 10.0);
    vec4 tmp = (ils0 * vec4(0.5, 0.5, 0.5, 1.0)) + 0.15 * acouleur + 0.55 * ild0 * couleur;


    vec3 Ld1 = normalize(lumpos1.xyz - mpos.xyz);
    float lumposDistance1 = length(lumpos1.xyz - mpos.xyz);
    vec3 lumposColor1 = vec3(1.0, 0.5, 0.0) / (lumposDistance1 * lumposDistance1);
    float attenuation1 = 0.10 / (1.0 + 0.05 * lumposDistance1 + 0.5 * lumposDistance1 * lumposDistance1);
    vec3 result1 = lumposColor1 * attenuation1;
    tmp.rgb += result1;

    vec3 Ld2 = normalize(lumpos2.xyz - mpos.xyz);
    float lumposDistance2 = length(lumpos2.xyz - mpos.xyz);
    vec3 lumposColor2 = vec3(1.0, 0.0, 0.0) / (lumposDistance2 * lumposDistance2);
    float attenuation2 = 0.95 / (1.0 + 0.05 * lumposDistance2 + 0.05 * lumposDistance2 * lumposDistance2);
    vec3 result2 = lumposColor2 * attenuation2;
    tmp.rgb += result2;

    vec3 Ld3 = normalize(lumpos3.xyz - mpos.xyz);
    float lumposDistance3 = length(lumpos3.xyz - mpos.xyz);
    vec3 lumposColor3 = vec3(1.0, 1.0, 1.0) / (lumposDistance3 * lumposDistance3);
    float attenuation3 = 0.05 / (1.0 + 0.05 * lumposDistance3 + 0.01 * lumposDistance3 * lumposDistance3);  
    vec3 result3 = lumposColor3 * attenuation3;
    tmp.rgb += result3;

    vec3 Ld4 = normalize(lumpos4.xyz - mpos.xyz);
    float lumposDistance4 = length(lumpos4.xyz - mpos.xyz);
    vec3 lumposColor4 = vec3(1.0, 0.35, 0.0) / (lumposDistance4 * lumposDistance4);
    float attenuation4 = 0.5 / (1.0 + 0.05 * lumposDistance4 + 0.005 * lumposDistance4 * lumposDistance4);
    vec3 result4 = lumposColor4 * attenuation4;
    tmp.rgb += result4;

    vec3 Ld5 = normalize(lumpos5.xyz - mpos.xyz);
    float lumposDistance5 = length(lumpos5.xyz - mpos.xyz);
    vec3 lumposColor5 = vec3(0.5, 0.6, 1.0) / (lumposDistance5 * lumposDistance5);
    float attenuation5 = 0.25 / (1.0 + 0.05 * lumposDistance5 + 0.005 * lumposDistance5 * lumposDistance5);
    vec3 result5 = lumposColor5 * attenuation5;
    tmp.rgb += result5;

    vec3 Ld6 = normalize(lumpos6.xyz - mpos.xyz);
    float lumposDistance6 = length(lumpos6.xyz - mpos.xyz);
    vec3 lumposColor6 = vec3(1.0, 0.2, 0.0) / (lumposDistance6 * lumposDistance6);
    float attenuation6 = 0.45 / (1.0 + 0.05 * lumposDistance6 + 0.005 * lumposDistance6 * lumposDistance6);
    vec3 result6 = lumposColor6 * attenuation6;
    tmp.rgb += result6;

    if(use_tex == 1)
        fragColor = mix(tmp, texture(tex, tcoord), 0.25);
    else
        fragColor = tmp;
}
