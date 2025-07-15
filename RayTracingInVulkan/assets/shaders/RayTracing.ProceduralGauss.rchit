#version 460
#extension GL_EXT_nonuniform_qualifier : require
#extension GL_GOOGLE_include_directive : require
#extension GL_EXT_ray_tracing : require

#include "Gauss.glsl"
#include "RayPayload.glsl"

layout(binding = 13) buffer NextKBuffer { SplatInfo[][8] NextK; };
layout(binding = 14) buffer RayInfoBuffer { RayInfo[] Rays; };

hitAttributeEXT vec4 Sphere;
rayPayloadInEXT RayPayload Ray;

void main()
{
    // Get Ray's Gauss Info
    vec2 pixel = vec2(gl_LaunchIDEXT.xy);
    int ray_id = int(pixel.x) + 16 * int(pixel.y);

	// Alpha Blending
    float CurTrans = Ray.Trans;
    for (int i = 0; i < Rays[ray_id].GaussNum; i++) {
        SplatInfo Splat = NextK[ray_id][i];
        CurTrans *= (1 - Splat.alpha);
    }
    Ray.Trans = CurTrans;

    // Update the Ray Info
    int GaussIndex = Rays[ray_id].GaussNum - 1;
    Rays[ray_id].Depth = NextK[ray_id][GaussIndex].depth;
	
}
