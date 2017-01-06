#version 420 core

uniform sampler2D heightmapTex;
uniform sampler2D snowTex;
uniform sampler2D gravelTex;
uniform sampler2D sandTex;

uniform vec3 cameraPos;
uniform vec4 lightColour;
uniform vec3 lightPos;
uniform float lightRadius;

uniform float groundTypeAmount;

in G_OUT {
    vec3 normal;
    vec2 texCoord;
    vec3 worldPos;
} fs_in;

void main() {
    //** CALCULATE LIGHT **//
	vec3 incident = normalize ( lightPos - fs_in.worldPos );
	vec3 viewDir = normalize ( cameraPos - fs_in.worldPos );
	vec3 halfDir = normalize ( incident + viewDir );
    
    float dist = length ( lightPos - fs_in.worldPos );
	float atten = 1.0 - clamp ( dist / lightRadius , 0.0 , 1.0);
    
    float lambert = max (0.0 , dot ( incident , fs_in.normal ));

	float rFactor = max (0.0 , dot ( halfDir , fs_in.normal ));
	float sFactor = pow ( rFactor , 50.0 );

    vec4 texHeight  = texture(heightmapTex, fs_in.texCoord);
    vec4 snowCol    = texture(snowTex,      fs_in.texCoord);
    vec4 gravelCol  = texture(gravelTex,    fs_in.texCoord);
    vec4 sandCol    = texture(sandTex,      fs_in.texCoord);
    

    vec4 texCol = mix(gravelCol, snowCol, texHeight);
    if(texHeight.r < groundTypeAmount) { // 0.3 good
        vec4 c = mix(gravelCol, sandCol, texHeight);
        texCol = mix(c, texCol, texHeight);
    }
    
	vec3 ambient = texCol.rgb * lightColour.xyz * 0.1;
	vec3 diffuse = texCol.rgb * lightColour.xyz * lambert * atten;
	vec3 specular = lightColour.xyz * sFactor * atten;
    //** END LIGHT **//
    

    // SHOW NORMALS
    //gl_FragColor = vec4(fs_in.normal, 1.0f);
    
    // SHOW TEXTURE
    //gl_FragColor = texture(heightmapTex, fs_in.texCoord);

    // SHOW TEXTURE WITH LIGHTING
    //gl_FragColor = vec4 ( ambient + diffuse + specular , texCol.a );
    gl_FragColor = vec4 ( ambient + diffuse, texCol.a );
}