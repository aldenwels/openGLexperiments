#version 410 core
/*
 Mixes color based on distance from point defined in this case as (1,1)
 */
in vec4 gl_FragCoord;
out vec4 color;
uniform vec2 resolution = vec2(1200,1600);
uniform float time;

vec3 colorA = vec3(0.195,0.912,0.027);
vec3 colorB = vec3(1.000,0.950,0.994);

void main() {
    
    vec2 st = gl_FragCoord.xy/resolution;
    float pct = 0.0;
    pct = distance(st,vec2(1));
    vec3 c = mix(colorA,colorB,pct);
    color = vec4(c,1.0);
    
}

