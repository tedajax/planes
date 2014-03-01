#include "color.h"
#include <math.h>

SDL_Color color_convertHSV(ColorHSV *hsvColor) {
	f32 h = hsvColor->h, s = hsvColor->s, v = hsvColor->v;

	while (h > 360.0f) { h -= 360.0f; }
	while (h < 0.0f) { h += 360.0f; }

	f32 c = v * s;
	f32 x = c * (1 - fabs((((int)(h / 60.0f)) % 2) - 1));
	f32 m = v - c;

	f32 rp = 0.0f, gp = 0.0f, bp = 0.0f;
	if (h >= 300.0f) {
		rp = c;
		bp = x;
	} else if (h >= 240.0f) {
		rp = x;
		bp = c;
	} else if (h >= 180.0f) {
		gp = x;
		bp = c;
	} else if (h >= 120.0f) {
		gp = c;
		bp = x;
	} else if (h >= 60.0f) {
		rp = x;
		gp = c;
	} else {
		rp = c;
		gp = c;
	}

	u8 r = ((rp + m) * 255.0f);
	u8 g = ((gp + m) * 255.0f);
	u8 b = ((bp + m) * 255.0f);
	printf("%u \n", r);

	SDL_Color result;
	result.r = r;
	result.g = g;
	result.b = b;
	result.a = hsvColor->a * 255;
	
	return result;
}

ColorHSV color_convertRGB(SDL_Color *rgbColor) {
	ColorHSV hsv;
	return hsv;
}
