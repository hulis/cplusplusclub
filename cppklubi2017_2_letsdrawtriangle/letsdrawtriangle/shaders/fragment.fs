#version 330

in vec4 v_color;

out vec4 color;

uniform float u_time;

void main()
{
	color = vec4(
		abs(sin(u_time) * v_color.x),
		abs(cos(u_time) * v_color.y),
		abs(tan(u_time) * v_color.z),
		v_color.w
	);
	
	//color = v_color;
	/*color = vec4(
				sin(u_time) / 2 + 0.50,
				cos(u_time) / 2 + 0.50,
				0.33,
				1.0);*/
}