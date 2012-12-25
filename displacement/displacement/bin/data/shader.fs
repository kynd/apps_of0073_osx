
varying vec3 p;
varying vec3 n;
uniform sampler2D tex0;
uniform sampler2D tex1;

void main(void) 
{
	vec4 mapColor = texture2D(tex1, gl_TexCoord[0].st);
	vec2 pos = gl_TexCoord[0].st;
	pos.s += ((mapColor.r - 0.5) / 1280.0);
	pos.t += ((mapColor.g - 0.5) / 720.0);
	vec4 color = texture2D(tex0, pos);
	gl_FragColor = color;
}