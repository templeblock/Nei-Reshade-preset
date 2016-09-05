//Stuff all/most of McFX shared shaders need
NAMESPACE_ENTER(MFX)
#define MFX_SETTINGS_DEF "ReShade/McFX.cfg"
#define MFX_SETTINGS_UNDEF "ReShade/McFX.undef" 

#include MFX_SETTINGS_DEF

#if( HDR_MODE == 0)
 #define RENDERMODE RGBA8
#elif( HDR_MODE == 1)
 #define RENDERMODE RGBA16F
#else
 #define RENDERMODE RGBA32F
#endif

//global vars
#define ScreenSize 	float4(BUFFER_WIDTH, BUFFER_RCP_WIDTH, float(BUFFER_WIDTH) / float(BUFFER_HEIGHT), float(BUFFER_HEIGHT) / float(BUFFER_WIDTH)) //x=Width, y=1/Width, z=ScreenScaleY, w=1/ScreenScaleY
#define PixelSize  	float2(BUFFER_RCP_WIDTH, BUFFER_RCP_HEIGHT)
#define PI 		3.1415972
#define PIOVER180 	0.017453292
#define AUTHOR 		MartyMcFly
#define FOV 		75
#define MFX_LumCoeff 	float3(0.212656, 0.715158, 0.072186)
#define zFarPlane 	1
#define zNearPlane 	0.001		//I know, weird values but ReShade's depthbuffer is ... odd
#define aspect          (BUFFER_RCP_HEIGHT/BUFFER_RCP_WIDTH)
#define InvFocalLen 	float2(tan(0.5f*radians(FOV)) / (float)BUFFER_RCP_HEIGHT * (float)BUFFER_RCP_WIDTH, tan(0.5f*radians(FOV)))

//textures
texture2D texNoise      < string source = "ReShade/McFX/Textures/mcnoise.png"; > {Width = BUFFER_WIDTH;Height = BUFFER_HEIGHT;Format = RGBA8;};

//samplers
sampler2D SamplerNoise
{
	Texture = texNoise;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

#include MFX_SETTINGS_UNDEF

NAMESPACE_LEAVE()

#pragma message "McFX 1.1.450 by Marty McFly\n"
