NAMESPACE_ENTER(CFX)

#include CFX_SETTINGS_DEF

#if USE_YACA

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ReShade effect file
// visit facebook.com/MartyMcModding for news/updates
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Yet Another Chromatic Aberration by Marty McFly
// For private use only!
// Copyright � 2008-2015 Marty McFly
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
   
/////////////////////////PIXEL SHADERS//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////PIXEL SHADERS//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
float4 PS_YACA(float4 vpos : SV_Position, float2 texcoord : TEXCOORD) : SV_Target
{  
        float4 scenecolor = 0;
 
        float2 coord=texcoord.xy*2.0-1.0;
        float offsetfact=length(texcoord.xy*2.0-1.0);
        offsetfact=pow(offsetfact,fADOF_ImageChromaCurve)*fADOF_ImageChromaAmount*BUFFER_RCP_WIDTH;
 
        float3 chromaweight = 0.0;
 
        [unroll]
        for (float c=0; c<iADOF_ImageChromaHues && c < 90; c++)
        {
                float temphue = c/iADOF_ImageChromaHues;
                float3 tempchroma = saturate(float3(abs(temphue * 6.0 - 3.0) - 1.0,2.0 - abs(temphue * 6.0 - 2.0),2.0 - abs(temphue * 6.0 - 4.0)));
                float  tempoffset = (c + 0.5)/iADOF_ImageChromaHues - 0.5;
                float3 tempsample = tex2Dlod(RFX_backbufferColor, float4(coord.xy*(1.0+offsetfact*tempoffset)*0.5+0.5,0,0)).xyz;
                scenecolor.xyz += tempsample.xyz*tempchroma.xyz;
                chromaweight += tempchroma;
        }
        //not all hues have the same brightness, FF0000 and FFFF00 are obviously differently bright but are just different hues.
        //there is no generic way to make it work for all different hue options. Sometimes / samples * 0.5 works, then * 0.666, then something completely different.
        scenecolor.xyz /= dot(chromaweight.xyz, 0.333);
 
        return scenecolor;
}

technique YACA_Tech <bool enabled = RFX_Start_Enabled; int toggle = YACA_ToggleKey; >
{
	pass YACAPass
	{
		VertexShader = RFX_VS_PostProcess;
		PixelShader = PS_YACA;
	}
}

#endif

#include CFX_SETTINGS_UNDEF

NAMESPACE_LEAVE()
