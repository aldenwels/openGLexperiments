#version 410 core

in vec4 gl_FragCoord;
out vec4 color;
uniform vec2 resolution = vec2(1200,1600);
vec3 colorA = vec3(0.149,0.141,0.912);
vec3 colorB = vec3(1.000,0.833,0.224);

float plot(vec2 st, float pct){
    return  smoothstep( pct-0.02, pct, st.y) -
    smoothstep( pct, pct+0.02, st.y);
}

void main() {
    vec2 st = gl_FragCoord.xy/resolution;
    
    vec3 pct = vec3(st.x);
    vec3 c = vec3(0.0);
    c = mix(colorA,colorB,pct);
    
    // Plot transition lines for each channel
    c = mix(c,vec3(1.0,0.0,0.0),plot(st,pct.r));
    c = mix(c,vec3(0.0,1.0,0.0),plot(st,pct.g));
    c = mix(c,vec3(0.0,0.0,1.0),plot(st,pct.b));
   
    color = vec4(c,1.0);
}

