
struct RayPayload
{
	float Trans; // WLZ
	vec4 ColorAndDistance; // rgb + t
	vec4 ScatterDirection; // xyz + w (is scatter needed)
	vec3 SurfaceNormal;
	uint RandomSeed;
};

// WLZ
struct RayInfo
{
    float Depth;
    int GaussNum;
};