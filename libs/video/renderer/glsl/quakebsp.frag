uniform sampler2D palette;
uniform sampler2D colormap;
uniform sampler2D texture;
uniform sampler2D lightmap;

varying vec2 tst;
varying vec2 lst;

void
main (void)
{
	float       pix = texture2D (texture, tst).r;
	float       light = texture2D (lightmap, lst).r;
	float       col;

	col = texture2D (colormap, vec2 (pix, light * 4.0)).r;
	gl_FragColor = texture2D (palette, vec2 (col, 0.5));
}