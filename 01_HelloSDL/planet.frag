#version 460 core
#extension GL_NV_shadow_samplers_cube : enable

#define M_PI 3.14159265359

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
    float shininess;
};

struct Hit 
{
    float t;
    vec3 position;
    vec3 normal;
    int planetIndex;
};

struct Light
{
    vec3 position;

    float constant;
    float linear;
    float quadratic;
  
    vec3 ambient; 
    vec3 diffuse;
    vec3 specular;
};

struct Ray 
{
    vec3 startPos;
	vec3 direction;
};

struct Camera 
{
    vec3 position;
    
    vec3 frontAxis;
    vec3 sideAxis;
    vec3 upAxis;

    float fov;
    float width;
    float height;
};

struct Planet
{
    vec3 position;
    float radius;

    int materialIndex;
    int textureIndex;
};

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

out vec4 FragColor;

uniform Camera camera; 

uniform Planet planets[15];
uniform int planetCount;  

uniform sampler2D textures[15];
uniform samplerCube cubemapTexture;

uniform Light lights[4];
uniform int lightCount;

uniform Material materials[15];
uniform int materialCount;

uniform int maxDepth;
uniform vec3 worldAmbient;

Hit intersect (Ray ray, int planetIndex)
{
    Planet planet = planets[planetIndex];
    Hit hit;
	hit.t = -1;

	vec3 dist = ray.startPos - planet.position;

	float a = dot(ray.direction, ray.direction);
	float b = dot(dist, ray.direction) * 2.0f;
	float c = dot(dist, dist) - planet.radius * planet.radius;
	float discr = b * b - 4.0f * a * c;
	if (discr < 0) return hit;

	float sqrt_discr = sqrt(discr);
	float t1 = (-b + sqrt_discr) / 2.0f / a;
	float t2 = (-b - sqrt_discr) / 2.0f / a;
	if (t1 <= 0) return hit;
	hit.t = (t2 > 0) ? t2 : t1;

	hit.position = ray.startPos + ray.direction * hit.t;
	hit.normal = (hit.position - planet.position) / planet.radius;
	hit.planetIndex = planetIndex;

	return hit;
}

Hit firstIntersection(Ray ray) 
{
    Hit bestHit;
	bestHit.t = -1;

	for (int i = 0; i < planetCount; i++) 
    {
		Hit hit = intersect(ray, i);

		if (hit.t > 0 && (bestHit.t < 0 || hit.t < bestHit.t))  
            bestHit = hit;
	}

	if (dot(ray.direction, bestHit.normal) > 0) 
        bestHit.normal = bestHit.normal * (-1);
	
    return bestHit;
}

bool inShadow(Hit hit, Ray shadowRay, Light light)
{
    Hit shadowHit = firstIntersection(shadowRay);
    if (shadowHit.t > 0)
    {
        float distToLight = length(light.position - hit.position);
        float distToShadowHit = length(shadowHit.position - hit.position);

        if (shadowHit.planetIndex > 0 && distToShadowHit < distToLight)
			return true;
    }

    return false;
}

vec2 calculateSphereTextCoords(Hit hit)
{
    int textureIndex = planets[hit.planetIndex].textureIndex;
    
    if (textureIndex <= -1)
	{
        return vec2(0.0);
    }

	vec3 hitNormal = hit.normal * planets[hit.planetIndex].radius;
    float u = 0.5 + atan(hitNormal.z, hitNormal.x) / (2.0 * M_PI);
    float v = 0.5 - asin(hitNormal.y / planets[hit.planetIndex].radius) / M_PI;
    
    return vec2(u, v);
}

vec3 calculateLighting(Ray ray, Hit hit)
{
    float epsilon = 0.1;
    vec3 outColor = vec3(0.0);

    if (hit.planetIndex == 0)
    {
        vec2 sphereTextCoords = calculateSphereTextCoords(hit);
        return texture(textures[0], sphereTextCoords).rgb * 1.5;
    }

    for (int i = 0; i < lightCount; i++)
    {
        Ray shadowRay;
        shadowRay.startPos = hit.position + epsilon * hit.normal;
        shadowRay.direction = normalize(lights[i].position - hit.position);

        if (inShadow(hit, shadowRay, lights[i]))
			continue;

        float cosTheta = dot(hit.normal, shadowRay.direction);

        if (cosTheta > 0.0)
        {
            Material material = materials[planets[hit.planetIndex].materialIndex];

            // Ambient component
            vec3 ambient = material.ambient * lights[i].ambient;

            // Diffuse component
            vec3 diffuse = vec3(0.0);
            
            int textureIndex = planets[hit.planetIndex].textureIndex;
            if (textureIndex > -1)
			{
                vec2 sphereTextCoords = calculateSphereTextCoords(hit);
                diffuse = texture(textures[textureIndex], sphereTextCoords).rgb * lights[i].diffuse * cosTheta;
			}
            else
            {
                diffuse = material.diffuse * lights[i].diffuse * cosTheta;
            }

            // Specular component
            vec3 halfway = normalize(shadowRay.direction - ray.direction);
            float cosDelta = dot(hit.normal, halfway);
            vec3 specular = material.specular * lights[i].specular * pow(cosDelta, material.shininess);

            outColor += ambient + diffuse + specular;
        }
    }

    return outColor;
}

vec3 trace (Ray ray)
{
    const float epsilon = 0.1;
    vec3 color = vec3(0.0, 0.0, 0.0);

    vec3 averageLightPosition = vec3(0.0);

    for (int i = 0; i < lightCount; i++)
    {
        averageLightPosition += lights[i].position;
    }
    averageLightPosition /= lightCount;

    for (int d = 0; d < maxDepth; d++)
    {               
        Hit hit = firstIntersection(ray);

        if (hit.t <= 0.0)
		{
            if (d == 0)
            {
                color += textureCube(cubemapTexture, ray.direction).rgb;
                break;
            }

            color += worldAmbient;
            break;
        }

        if (d == 0)
        {
            float distance = length(camera.position - averageLightPosition);
            float distanceFactor = 1.0 / ( max (1.0, ( distance / 150 )));
            color += distanceFactor * calculateLighting(ray, hit);
        }
        else if (hit.planetIndex == 0)
        {
            break;
        }
        
        //visszaverodes a bolygokrol
        
        ray.startPos = hit.position + epsilon * hit.normal;
        ray.direction = reflect(ray.direction, hit.normal);
    }

	return color;
}

void main()
{ 
    Ray ray;
    ray.startPos = camera.position;
    
    float aspect = camera.width / camera.height;
    float alpha = tan(camera.fov / 2.0) * (gl_FragCoord.x - (camera.width / 2.0)) / (camera.width / 2.0);
    float beta = tan(camera.fov / 2.0) * ((camera.height / 2.0) - gl_FragCoord.y) / (camera.height / 2.0) / aspect;
    ray.direction = normalize(camera.frontAxis + alpha * camera.sideAxis - beta * camera.upAxis);

    vec3 result = trace(ray);

    FragColor = vec4(result, 1.0);
}