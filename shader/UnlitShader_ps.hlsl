struct PS_IN
{
    float4 pos : POSITION0;
    float4 col : COLOR0;
};
 
float4 main(PS_IN input) : SV_Target
{
    return input.col;
}
