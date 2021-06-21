#version 130
#ifdef GL_ES
precision mediump float;
#endif


uniform float Time;
uniform float Amplitude;
uniform sampler2D Text;

//uniform float Samples[2000];
uniform float currentSample;
uniform float rightChannel;
float box2(vec2 center, vec2 size, vec2 coord)
{

   vec2 b=smoothstep(center-size, center, coord)-smoothstep(center, center+size, coord);
		
      if(b.x>0 && b.y>0)
	  return 1.;
	  else
	  return 0.;

		}
		float box(float x, float y, float funcValue, float xRegion)
		{

		float line=smoothstep(funcValue-12.,funcValue,y)-smoothstep(funcValue, funcValue+12.,y);
	    float def=step(-1.*xRegion,x)-step(xRegion,x);
	
			if(def!=1.0)
			{
			line=0.;
			}
		return line;
}



void main()
{
 float ratioWH = 320.0 / 320.0;
 float ratioHW = 320.0/ 320.0;
 vec2 adjMul = vec2(ratioWH, 1.);
 vec2 adjSub = vec2((1.-ratioHW) * 0.5 * ratioWH, 0.);
 vec2 uv = (gl_FragCoord.xy/vec2(320.0,320.0)) * adjMul - adjSub;
	
float r=0;
for(int i=0; i<20; i++)
{
float x=floor(uv.x);
float y=uv.y*100.0-50.0;
vec2 center=vec2(i*0.05,0);
vec2 coord =vec2(uv.x,y);

//float height=Samples[int(Time*10)+i];
float height=sin(currentSample);
if(i>10)
height=sin(rightChannel);
r+=box2(center, vec2(0.01,height),coord );

}

gl_FragColor=vec4(r, 0,0,1.0);
}