
varying vec3 p;
varying vec3 n;

uniform sampler2D tex0;

void main(void) 
{
	vec4 texCol0 = texture2D(tex0, gl_TexCoord[0].st);
	if (gl_TexCoord[0].s > 0.2) {
		
		gl_FragColor = texCol0;
	} else {
	}
	
	
		gl_FragColor = vec4(1.0,0.0,0.0,1.0);
		gl_FragColor = texCol0;
}

