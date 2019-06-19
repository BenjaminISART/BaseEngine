#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 texcoord;

uniform vec3 lightpos;
uniform vec3 viewpos;
uniform vec3 lightcolor;
uniform vec3 viewDir;
uniform float lightshin;
uniform sampler2D ourTexture;

//*********************************************** types of light

struct DirLight {
     vec3 direction;
     vec3 ambient;
     vec3 diffuse;
     vec3 specular;
};
#define MAX_NB_DIRLIGHT 4
uniform int nb_dirLight;
uniform DirLight dirLight[MAX_NB_DIRLIGHT];
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);


//----------------------------------

struct PointLight {
     vec3 position;

     float constant;
     float linear;
     float quadratic;
     float ambientPower;

     vec3 ambient;
     vec3 diffuse;
     vec3 specular;
};
#define MAX_NB_POINTLIGHT 4
uniform int nb_pointLight;
uniform PointLight pointLight[MAX_NB_POINTLIGHT];
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

//----------------------------------

struct SpotLight {
     vec3 position;
     vec3 direction;
     float cutOff;
     float outerCutOff;

     float constant;
     float linear;
     float quadratic;

     vec3 ambient;
     vec3 diffuse;
     vec3 specular;
};
#define MAX_NB_SPOTLIGHT 4
uniform int nb_spotLight;
uniform SpotLight spotLight[MAX_NB_SPOTLIGHT];
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

//----------------------------------

struct Material
{
     sampler2D ambient;
     sampler2D diffuse;
     sampler2D specular;
     float shininess;
};

uniform Material material;

//----------------------------------

//***********************************************  (MAIN)

void main()
{
	// tmp
	dirLight[0].ambient = vec3(0.2f, 0.2f, 0.2f);
	dirLight[0].diffuse = vec3(0.2f, 0.2f, 0.2f);
	dirLight[0].specular = vec3(0.2f, 0.2f, 0.2f);
	dirLight[0].direction = vec3(0.0f, -1.0f, 0.0f);
	// /tmp

     // properties
     vec3 norm = normalize(Normal);
     vec3 viewDir = normalize(viewpos - FragPos);
     vec3 result;

     for(int i = 0; i < nb_dirLight; i++)
          result += CalcDirLight(dirLight[i], norm, viewDir);

     for(int i = 0; i < nb_pointLight; i++)
          result += CalcPointLight(pointLight[i], norm, FragPos, viewDir);
          
     for(int i = 0; i < nb_spotLight; i++)
          result += CalcSpotLight(spotLight[i], norm, FragPos, viewDir);

     FragColor = vec4(result, 1.0) * texture(ourTexture, texcoord);
}

//*************************************************

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
     vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, texcoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texcoord));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, texcoord));
    return (ambient + diffuse + specular);
}

//---------------------------------------------

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
     vec3 lightDir = normalize(light.position - fragPos);
     // diffuse shading
     float diff = max(dot(normal, lightDir), 0.0);
     // specular shading
     vec3 reflectDir = reflect(-lightDir, normal);
     float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
     // attenuation
     float distance = length(light.position - fragPos);
     float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
     // combine results
     vec3 ambient = light.ambient * vec3(texture(material.diffuse, texcoord));
     vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texcoord));
     vec3 specular = light.specular * spec * vec3(texture(material.specular, texcoord));
     ambient *= attenuation;
     diffuse *= attenuation;
     specular *= attenuation;
     return (ambient + diffuse + specular);
}

//-----------------------------------------------

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
     vec3 lightDir = normalize(light.position - fragPos);
     // diffuse shading
     float diff = max(dot(normal, lightDir), 0.0);
     // specular shading
     vec3 reflectDir = reflect(-lightDir, normal);
     float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
     // attenuation
     float distance = length(light.position - fragPos);
     float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
     // spotlight intensity
     float theta = dot(lightDir, normalize(-light.direction));
     float epsilon = light.cutOff - light.outerCutOff;
     float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
     // combine results
     vec3 ambient = light.ambient * vec3(texture(material.diffuse, texcoord));
     vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texcoord));
     vec3 specular = light.specular * spec * vec3(texture(material.specular, texcoord));
     ambient *= attenuation * intensity;
     diffuse *= attenuation * intensity;
     specular *= attenuation * intensity;
     return (ambient + diffuse + specular);
}

//-----------------------------------------------
