#version 420 core

uniform float time;

uniform sampler2D heightmapTex;

uniform vec3 cameraPos;
uniform vec4 lightColour;
uniform vec3 lightPos;
uniform float lightRadius;

uniform float ripple;
uniform float transparency;
uniform float waterRed;
uniform float waterGreen;
uniform float waterBlue;

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

    vec4 texCol = texture(heightmapTex, fs_in.texCoord);
	vec3 ambient = texCol.rgb * lightColour.xyz * 0.1;
	vec3 diffuse = texCol.rgb * lightColour.xyz * lambert * atten;
	vec3 specular = lightColour.xyz * sFactor * atten;
    
    // SHOW NORMALS
    //gl_FragColor = vec4(fs_in.normal, 1.0f);

    // WATER RIPPLE
    // Water source based on http://adrianboeing.blogspot.co.uk/2011/02/ripple-effect-in-webgl.html
    float msec = time / ripple;
    
    vec2 resolution = vec2(1920, 1080);
    vec2 cPos = -1.0 + 2.0 * gl_FragCoord.xy / resolution.xy;
    float cLength = length(cPos);

    vec2 uv = gl_FragCoord.xy / resolution.xy + (cPos / cLength) * cos(cLength * 12.0 - msec * 4.0) * 0.03;
    vec3 col = texture2D(heightmapTex,uv).xyz;
    vec3 s = vec3(waterRed, waterGreen, waterBlue);

    // SHOW TEXTURE 
    gl_FragColor = vec4( ambient + diffuse + specular, texCol.a ) * vec4(col * s , transparency);
}