//--------------------------------------------------------------------------------------
// File: CubeShader.fx
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
cbuffer ConstantBuffer1 : register( b0 )
{
    matrix View;
    matrix Projection;
};

cbuffer ConstantBuffer2 : register( b1 )
{
    matrix World;
    float4 vMeshColor;
};


//--------------------------------------------------------------------------------------
struct VS_INPUT
{
    float4 Pos : POSITION;
};

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
};


//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS( VS_INPUT input )
{
    PS_INPUT output = (PS_INPUT)0;
    output.Pos = mul( input.Pos, World );
    output.Pos = mul( output.Pos, View );
    output.Pos = mul( output.Pos, Projection );
    
    return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(PS_INPUT input) : SV_Target
{
    return vMeshColor;
}
