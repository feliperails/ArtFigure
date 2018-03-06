#version 330 core
uniform vec2 viewDimensions;
uniform float outerRadius;
out vec4 outColor;
void main()
{
   float x = (gl_FragCoord.x - viewDimensions.x / 2.0f) / (viewDimensions.x / 2.0f);
   float y = (gl_FragCoord.y - viewDimensions.y / 2.0f) / (viewDimensions.y / 2.0f);
   float len = sqrt(x * x + y * y);
	if (len > outerRadius) {
		discard;
	}
	outColor = vec4(0.0, 1.0, 0.0, 1.0);
}