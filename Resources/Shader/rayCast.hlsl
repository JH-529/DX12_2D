
cbuffer TRANSFORM_PARAMS : register(b0)
{
    row_major matrix matWVP;
};

SamplerState sam_0 : register(s0);

struct VS_IN
{
    float3 pos : POSITION;    
    float4 color : COLOR;
    float2 uv : TEXCOORD;
};

struct VS_OUT
{
    float4 pos : SV_Position;    
    float4 color : COLOR;
    float2 uv : TEXCOORD;
};

VS_OUT VS_Main(VS_IN input)
{
    VS_OUT output = (VS_OUT)0;

    output.pos = mul(float4(input.pos, 1.f), matWVP);
    output.color = input.color;
    output.uv = input.uv;

    return output;
}

float4 PS_Main(VS_OUT input) : SV_Target
{
    float4 color = (0.f, 1.f, 0.f, 0.f);
    return color;
}