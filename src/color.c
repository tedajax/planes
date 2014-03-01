#include "color.h"
#include <math.h>

SDL_Color color_convertHSV(ColorHSV *hsvColor) {
	f32 h = hsvColor->h, s = hsvColor->s, v = hsvColor->v;

	while (h > 360.0f) { h -= 360.0f; }
	while (h < 0.0f) { h += 360.0f; }

	f32 c = v * s;
	f32 x = c * (1.0f - fabs(fmod((h / 60.0f), 2) - 1.0f));
	f32 m = v - c;

	f32 rp = 0.0f, gp = 0.0f, bp = 0.0f;
	if (h < 60) {
		rp = c;
		gp = x;
	} else if (h < 120) {
		rp = x;
		gp = c;
	} else if (h < 180) {
		gp = c;
		bp = x;
	} else if (h < 240) {
		gp = x;
		bp = c;
	} else if (h < 300) {
		rp = x;
		bp = c;
	} else if (h < 360) {
		rp = c;
		bp = x;
	}

	u8 r = ((rp + m) * 255.0f);
	u8 g = ((gp + m) * 255.0f);
	u8 b = ((bp + m) * 255.0f);
	
	SDL_Color result;
	result.r = r;
	result.g = g;
	result.b = b;
	result.a = hsvColor->a * 255;
	
	return result;
}

bool color_testInput(float h, float s, float v, u8 r, u8 g, u8 b) {
	ColorHSV hsv;
	hsv.h = h;
	hsv.s = s;
	hsv.v = v;
	hsv.a = 1.0f;
	SDL_Color color = color_convertHSV(&hsv);

	return (color.r == r && color.g == g && color.b == b);
}

ColorHSV color_convertRGB(SDL_Color *rgbColor) {
	ColorHSV hsv;
	return hsv;
}
