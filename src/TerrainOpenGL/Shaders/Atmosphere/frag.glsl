#version 420 core

uniform float time;

uniform sampler2D heightmapTex;

uniform vec3 cameraPos;
uniform vec4 lightColour;
uniform vec3 lightPos;
uniform float lightRadius;

in G_OUT {
    vec3 normal;
    vec2 texCoord;
    vec3 worldPos;
} fs_in;

void main() {
    
    // SHOW NORMALS
    //gl_FragColor = vec4(fs_in.normal, 1.0f);

    // SHOW TEXTURE
    vec4 colour = texture(heightmapTex, fs_in.texCoord);
    vec4 alColour = vec4(colour.rbg, colour.r);
    
    if( colour.r < 0.4f ) {
        discard;
    }
    
    gl_FragColor = alColour;
}