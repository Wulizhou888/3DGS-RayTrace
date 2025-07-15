struct GaussParam 
{
	vec4 CenterOpacity;
    float Cov3D_0, Cov3D_1, Cov3D_2, Cov3D_3, Cov3D_4, Cov3D_5;
    float Pad_0, Pad_1;
};

struct SplatInfo
{
    float depth;
    float alpha;
}; 