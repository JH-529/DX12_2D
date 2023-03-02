
cbuffer TRANSFORM_PARAMS : register(b0)
{
    row_major matrix matWVP;
};

cbuffer MATERIAL_PARAMS : register(b1)
{
    int int_0;
    int int_1;
    int int_2;
    int int_3;
    int int_4;
    float float_0;
    float float_1;
    float float_2;
    float float_3;
    float float_4;
};

Texture2D tex_0 : register(t0);
SamplerState sam_0 : register(s0);

struct VS_IN
{
    float3 pos : POSITION;    
};

struct VS_OUT
{
    float4 pos : SV_Position;    
};

VS_OUT VS_Main(VS_IN input)
{
    VS_OUT output = (VS_OUT)0;

    output.pos = mul(float4(input.pos, 1.f), matWVP);

    return output;
}

float4 PS_Main(VS_OUT input) : SV_Target
{
    float4 color = {0.f, 1.f, 0.f, 0.f};

    if(!int_0)
        return color;        
    else
        color = {1.f, 0.f, 0.f, 0.f};

    return color;
}