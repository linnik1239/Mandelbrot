#version 330

in vec2 texCoord0;
in vec3 normal0;
in vec3 color0;
in vec3 position0;

uniform vec4 lightColor;
uniform sampler2D sampler;



uniform vec4 lightDirection;
uniform vec2 z;
uniform vec2 c;
uniform int p;
uniform int colorPower;

uniform float theMinusX;
uniform float thePlusX;
uniform float theMinusY;
uniform float thePlusY;


#define MAX_ITERATIONS 1000

float abs2(vec2 z){
    float abValue = sqrt(z.y*z.y+z.x*z.x);
    return abValue;

}

vec2 duplicateZ(vec2 z,int p){
   vec2 newZ = z;
   
   for(int i=0;i<p-1;++i){
      newZ = vec2(newZ.x*z.x -newZ.y*z.y,newZ.x*z.y +newZ.y*z.x);
   }
   
   return newZ;
}


int mandelbrot(vec2 c,int p){
   int n=0;
   vec2 z=vec2(0,0);
   
   while(abs2(z)<=2.0 && n<MAX_ITERATIONS){
      z = duplicateZ(z,p)+c;
      ++n;
   }

   return n;

}



void main()
{
    vec3 newColor = color0;
   
    vec2 c = vec2(theMinusX + texCoord0.x * (thePlusX -theMinusX),   theMinusY + texCoord0.y * (thePlusY-theMinusY) );
	
	int m = mandelbrot(c,p);     
	
	
	float Bcolor=0.0;
	if(m<MAX_ITERATIONS){
	   Bcolor = 1.0;
	}
	
	float color =  (m * 255.0 / 80.0);
	
	if(m>=MAX_ITERATIONS){
	    newColor = vec3(0,0,0);
	}else{
		newColor = (colorPower/255.0)*vec3(color/255.0,1.0,Bcolor);
	}

	//float k = m;
	//float div2 = k/MAX_ITERATIONS;
	//gl_FragColor = colorPower*texture(sampler1, div2);
	
	gl_FragColor = texture2D(sampler, texCoord0)* vec4(newColor,1.0);

}
