#version 400

uniform float zoom;
uniform float posX;
uniform float posY;
uniform vec2 aspectRatio;

double mandelbrot(vec2 uv)
{
	dvec2 c = dvec2(dvec2(aspectRatio * (dvec2(uv) - dvec2(0.5, 0.5)) / double(pow(4, zoom)) - dvec2(posX, posY)));
	dvec2 z = dvec2(0.0);
	double iter = 0.0;
	for(float i; i < 1000; i++)
	{
		z = dvec2(z.x * z.x - z.y * z.y, 2.0 * z.x * z.y) + c;
		if(dot(z, z) > 4.0) return iter / 20;
		iter++;
	}
	return 0.0;
}

void main()
{	
	vec2 uv = vec2(gl_FragCoord.x / 1920, gl_FragCoord.y / 1080);
	vec3 col = vec3(0.0);

	float m = float(mandelbrot(uv));
	col = vec3(sin(m), tan(m), tan(m));
	col = pow(col, vec3(0.45));

	gl_FragColor = vec4(col, 1.0);
}