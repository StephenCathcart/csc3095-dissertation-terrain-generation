#version 420 core

#define M_PI 3.1415926535897932384626433832795

layout(triangles, equal_spacing, cw) in;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;
uniform sampler2D heightmapTex;

uniform float time;
uniform float mountainScale;

uniform mat4 rotation;

out TES_OUT {
    vec3 normal;
    vec2 texCoord;
} tes_out;

void main(void) {
    vec3 p0 = gl_TessCoord.x * gl_in[0].gl_Position;
    vec3 p1 = gl_TessCoord.y * gl_in[1].gl_Position;
    vec3 p2 = gl_TessCoord.z * gl_in[2].gl_Position;
    vec3 tePosition = normalize(p0 + p1 + p2);
    
    // CALCULATE NORMAL
    mat3 normalMatrix = transpose(inverse(mat3(modelMatrix)));
    tes_out.normal = normalize(p0 + p1 + p2);
    
    // USE NORMALS TO WORK OUT TEXTURE UV COORDS
    tes_out.texCoord = vec2(asin(tes_out.normal.x) / M_PI + 0.5, asin(tes_out.normal.y)/ M_PI + 0.5);

    // CALCULATE HEIGHT FROM TEX
    vec4 tex = texture(heightmapTex, tes_out.texCoord);
    float r = tex.r / mountainScale; // Adjusts max height
    vec4 heightmapPos = vec4(tes_out.normal * r, 0.0) + vec4(tePosition, 1);

    // SET FINAL MVP POSITION
    mat4 mvp =  projMatrix * viewMatrix * modelMatrix; 
    gl_Position = mvp * heightmapPos;
}