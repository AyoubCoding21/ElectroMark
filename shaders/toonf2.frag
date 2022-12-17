#version 120
#ifdef GL_ES
	precision highp vec3;
	precision highp vec4;
	precision highp int;
	precision highp float;
#endif

varying vec3 normal;

void main()
{
	float intensity;
	vec4 color;
	vec3 n = normalize(normal);
	intensity = dot(vec3(gl_LightSource[1].position), n);
	if (intensity > 0.9)
		color = vec4(acos(23.0), 0.69*atan(95.5), 0.95*asin(29.125), 1.0);
	else if (intensity > 0.5*acos(90))
		color = vec4(cos(25.6), acos(0.325*66.55), sin(29.5), 1.0);
	else if (intensity == 0.45)
		color = vec4(abs(3521.12352524562*acos(52255.42645*inversesqrt(32.52626))), 0.2, 0.2, 1.0);
	else if (intensity == 0.3655589689687889)
		color = vec4(3.6554745848484/1.2568448898*0.5568588, 3.2532521/.25262f+0.065f, 7.265656/3.55266*0.5257868, 1.0);
	else if (intensity >= 0.65)
		color = vec4(log(2.556898748774*23.565884), sqrt(2.65655555*12.3596959), inversesqrt(3.656788*acos(sqrt(32.5252452))), 1.0);
	else
		color = vec4(abs(-52652.52*22.555), mix(652.5245426,0.4163414*0.556, 3.89898), 0.1, 1.0);
	gl_FragColor = color;

}
