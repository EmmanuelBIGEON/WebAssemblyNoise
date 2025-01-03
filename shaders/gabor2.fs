#version 300 es
precision highp float;

uniform vec2 resolution;
uniform float time;
out vec4 fragColor;

#define PI 3.14159265358979

int windows = 0;
vec2 m = vec2(.7,.8);

float hash( in vec2 p ) 
{
    return fract(sin(p.x*15.32+p.y*5.78) * 43758.236237153);
}


vec2 hash2(vec2 p)
{
	return vec2(hash(p*.754),hash(1.5743*p.yx+4.5891))-.5;
}

vec2 hash2b( vec2 p )
{
    vec2 q = vec2( dot(p,vec2(127.1,311.7)), 
				   dot(p,vec2(269.5,183.3)) );
	return fract(sin(q)*43758.5453)-.5;
}


mat2 m2= mat2(.8,.6,-.6,.8);

// Gabor/Voronoi mix 3x3 kernel (some artifacts for v=1.)
float gavoronoi3(in vec2 p)
{    
    vec2 ip = floor(p);
    vec2 fp = fract(p);
    float f = 2.*PI;//frequency
    float v = .8;//cell variability <1.
    float dv = .4;//direction variability <1.
    vec2 dir = m;//vec2(.7,.7);
    float va = 0.0;
   	float wt = 0.0;
    for (int i=-1; i<=1; i++) 
	for (int j=-1; j<=1; j++) 
	{		
        vec2 o = vec2(i, j)-.5;
        vec2 h = hash2(ip - o);
        vec2 pp = fp +o  -h;
        float d = dot(pp, pp);
        float w = exp(-d*4.);
        wt +=w;
        h = dv*h+dir;//h=normalize(h+dir);
        va += cos(dot(pp,h)*f/v)*w;
	}    
    return va/wt;
}


// Gabor/Voronoi mix 4x4 kernel (clean but slower)
float gavoronoi4(in vec2 p)
{    

    vec2 ip = floor(p);
    vec2 fp = fract(p);
    vec2 dir = m;// vec2(.9,.7);
    float f = 2.*PI;
    float v = 1.;//cell variability <1.
    float dv = .7;//direction variability <1.
    float va = 0.0;
   	float wt = 4.0;
    for (int i=-2; i<=1; i++) 
	for (int j=-2; j<=1; j++) 
	{		
        vec2 o = vec2(i, j);
        vec2 h = hash2(ip - o);
        vec2 pp = fp +o  -v*h;
        return pp.y;
        float d = dot(pp, pp);
        float w = exp(-d*2.);
        wt +=w;
      	h= dv*h+dir;//h=normalize(h+dir);
        va +=cos(dot(pp,h)*f)*w;
	}    
    return va/wt;
}

// Gabor/Voronoi mix 5x5 kernel (even slower but suitable for large wavelets)
float gavoronoi5(in vec2 p) 
{    
    vec2 ip = floor(p);
    vec2 fp = fract(p);
    float f = 2.*PI;//frequency
    float v = .8;//cell variability <1.
    float dv = .8;//direction variability <1.
    vec2 dir = m;//vec2(.7,.7);
    float va = 0.0;
   	float wt = 0.0;
    for (int i=-2; i<=2; i++) 
	for (int j=-2; j<=2; j++) 
	{		
        vec2 o = vec2(i, j)-.5;
        vec2 h = hash2(ip - o);
        vec2 pp = fp +o  -h;
        float d = dot(pp, pp);
        float w = exp(-d*1.);
        wt +=w;
        h = dv*h+dir;//h=normalize(h+dir);
        va += cos(dot(pp,h)*f/v)*w;
	}    
    return va/wt;
}

  

//concentric waves variant
float gavoronoi3b(in vec2 p)
{    
    vec2 ip = floor(p);
    vec2 fp = fract(p);
    float f = 5.*PI;
    float v = 1.;//cell variability <1.
    float va = 0.0;
    float wt = 0.0;
    for (int i=-1; i<=1; i++) 
	for (int j=-1; j<=1; j++) 
	{		
        vec2 o = vec2(i, j)-.5;       		
        vec2 pp = fp +o  - v*hash2(ip - o);
        float d = dot(pp, pp);
        float w = exp(-d*4.);
        wt +=w;
        va +=cos(sqrt(d)*f)*w;
	}    
    return va/wt;
}



float noise( vec2 p)
{   
    return gavoronoi4(p);
}

float fbmabs( vec2 p ) {
	
	float f=1.;
   
	float r = 0.0;	
    for(int i = 0;i<6;i++){	
		r += abs(noise( p*f ))/f;       
	    f *=2.2;
        p+=vec2(-.01,.07)*r+.2*m*time/(.1-f);
	}
	return r;
}

float fbm( vec2 p ) {
	
	float f=1.;
   
	float r = 0.0;	
    for(int i = 0;i<8;i++){	
		r += noise( p*f )/f;       
	    f *=2.;
        p+=vec2(.01,-.05)*r+.2*m*time/(.1-f);
	}
	return r;
}

float map(vec2 p){

    if(windows==0)return noise(p*10.);
    if(windows==1)return 2.*abs( noise(p*10.));
	if(windows==2)return fbm(p)+1.;
    return 1.-fbmabs(p);
}

vec3 nor(in vec2 p)
{
	const vec2 e = vec2(0.002, 0.0);
	return -normalize(vec3(
		map(p + e.xy) - map(p - e.xy),
		map(p + e.yx) - map(p - e.yx),
		.15));
}

	
void main() {
	
	vec2 p = 2.*gl_FragCoord.xy /resolution.xy-1.;
    
	if(p.y>0.){
    	if(p.x>0.)windows =1;
    	else    windows =0;}
    else{
    	if(p.x>0.)windows =3;
        else windows =2;}
    //comment the following line to see windows
    //windows =3;
   
      
   	p += .2*time;
    vec3 light = normalize(vec3(3., 2., -1.));
	float r;
    r = max(dot(nor(p), light),0.25);
    float k=map(p)*.8+.15;
    fragColor = clamp(vec4(r, r, r, 1.0),0.,1.);
	fragColor = clamp(vec4(r*k*k, r*k, r*sqrt(k), 1.0),0.,1.);
}