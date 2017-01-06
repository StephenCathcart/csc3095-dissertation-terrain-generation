#version 420 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in TES_OUT {
    vec3 normal;
    vec2 texCoord;
} g_in[];

out G_OUT {
    vec3 normal;
    vec2 texCoord;
    vec3 worldPos;
} g_out;

void main(void) {
    int i;
    for(i = 0; i < gl_in.length(); i++) {
        g_out.normal = g_in[i].normal;

        g_out.texCoord = g_in[i].texCoord;
        
        g_out.worldPos = gl_in[i].gl_Position;
        
        gl_Position = gl_in[i].gl_Position;
        
        EmitVertex();
    }
}