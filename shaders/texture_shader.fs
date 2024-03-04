#version 410 core

in vec2 v_TextureUVs;
in vec3 v_WorldVertex;
in vec3 v_WorldNormal;


uniform sampler2D uv_DiffuseSamplers[10];
uniform sampler2D uv_SpecularSamplers[10];
out vec4 f_Color;

void main() {
    //*********************
    // Camera
    vec3 cameraPos = vec3(0.0, 0.0, 0.0);

    //*********************
    // Basic Light Properties

    vec3 lightColor = vec3(1.0, 1.0, 1.0);
    vec3 lightPos = vec3(0.0, 5.0, 1.0);
    float lightAmbientIntensity = 0.1;

    //*********************
    // Ambient Calculations

    // AmbientStrength represents what fraction of the original light is now avaiable in the background. 
    float ambientStrenth = lightAmbientIntensity; 
    vec3 ambient = ambientStrenth * lightColor;


    //*********************
    // Diffuse Calculations

    vec3 norm = normalize(v_WorldNormal);
    vec3 toLight = normalize(lightPos - v_WorldVertex);
    float diff = max(dot(toLight, norm), 0.0);
    vec3 diffuse = diff * lightColor;


    //*********************
    // Specular Calculations

    float reflectivity = 0.5;
    vec3 toEye = normalize(cameraPos - v_WorldVertex);
    vec3 reflectedRay = reflect(-toLight, norm);  
    float disperseFactor = pow(max(dot(toEye, reflectedRay), 0.0), 32);
    vec3 specular = disperseFactor * (reflectivity * lightColor); 


    //*********************
    // Results

    vec3 fragColor = texture(uv_DiffuseSamplers[0], v_TextureUVs).xyz;
    vec3 result = ( ambient + diffuse + specular ) * fragColor;

    f_Color = vec4(result, 1.0); 
}