#version 150

uniform float iTime;
uniform float posX;
uniform float posY;

float mandelbrot(vec2 uv)
{
	vec2 c = 10 * (uv - vec2(posX, posY) * 1080 / 1920);
	c = c / pow(iTime, 4.0) - vec2(posX, posY) * 1080 / 1920;
	vec2 z = vec2(0.0);
	float iter = 0.0;
	for(float i; i < 3000.0; i++)
	{
		z = vec2(z.x * z.x - z.y * z.y, 2.0 * z.x * z.y) + c;
		if(dot(z, z) > 4.0) return iter / 3000.0;
		iter++;
	}
	return 0.0;
}

void main()
{	
	vec2 uv = gl_FragCoord.xy / 1920.0;
	vec3 col = vec3(0.0);

	float m = mandelbrot(uv);
	if(m > 0.9) col.x += m;
	else if(m > 0.1) col.y += m;
	col.z += m;
	col = pow(col, vec3(0.45));

	gl_FragColor = vec4(col, 1.0);
}