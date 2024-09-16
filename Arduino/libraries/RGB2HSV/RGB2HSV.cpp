#include "RGB2HSV.h"

RgbColor HsvToRgb(HsvColor hsv) {
	RgbColor rgb;
	unsigned char region, remainder, p, q, t;

	// saturation = 0 -> trivial conversion to rgb(0,0,0)
	if (hsv.m_s == 0) {
		rgb.m_r = hsv.m_v;
		rgb.m_g = hsv.m_v;
		rgb.m_b = hsv.m_v;
		return rgb;
	}

	// clip input to range
	while (hsv.m_h > 255)
		hsv.m_h -= 256;
	if (hsv.m_v > 255)
		hsv.m_h = 255;
	if (hsv.m_s > 255)
		hsv.m_s = 255;

	region = hsv.m_h / 43;
	remainder = (hsv.m_h - (region * 43)) * 6; 

	p = (hsv.m_v * (255 - hsv.m_s)) >> 8;
	q = (hsv.m_v * (255 - ((hsv.m_s * remainder) >> 8))) >> 8;
	t = (hsv.m_v * (255 - ((hsv.m_s * (255 - (unsigned int)remainder)) >> 8))) >> 8; // require compiler to use 16bit calculation

	switch (region) {
		case 0:
			rgb.m_r = hsv.m_v; rgb.m_g = t; rgb.m_b = p;
			break;
		case 1:
			rgb.m_r = q; rgb.m_g = hsv.m_v; rgb.m_b = p;
			break;
		case 2:
			rgb.m_r = p; rgb.m_g = hsv.m_v; rgb.m_b = t;
			break;
		case 3:
			rgb.m_r = p; rgb.m_g = q; rgb.m_b = hsv.m_v;
			break;
		case 4:
			rgb.m_r = t; rgb.m_g = p; rgb.m_b = hsv.m_v;
			break;
		default:
			rgb.m_r = hsv.m_v; rgb.m_g = p; rgb.m_b = q;
			break;
	}

	return rgb;
}


HsvColor RgbToHsv(RgbColor rgb) {
	HsvColor hsv;
	unsigned char rgbMin, rgbMax;

	// clip input to range
	if (rgb.m_r > 255)
		rgb.m_r = 255;
	if (rgb.m_g > 255)
		rgb.m_g = 255;
	if (rgb.m_b > 255)
		rgb.m_b = 255;

	rgbMin = rgb.m_r < rgb.m_g ? (rgb.m_r < rgb.m_b ? rgb.m_r : rgb.m_b) : (rgb.m_g < rgb.m_b ? rgb.m_g : rgb.m_b);
	rgbMax = rgb.m_r > rgb.m_g ? (rgb.m_r > rgb.m_b ? rgb.m_r : rgb.m_b) : (rgb.m_g > rgb.m_b ? rgb.m_g : rgb.m_b);
	
	hsv.m_v = rgbMax;
	if (hsv.m_v == 0)
	{
		hsv.m_h = 0;
		hsv.m_s = 0;
		return hsv;
	}

	hsv.m_s = 255 * long(rgbMax - rgbMin) / hsv.m_v;
	if (hsv.m_s == 0)
	{
		hsv.m_h = 0;
		return hsv;
	}

	if (rgbMax == rgb.m_r)
		hsv.m_h = 0 + (unsigned int)43 * (rgb.m_g - rgb.m_b) / (rgbMax - rgbMin);
	else if (rgbMax == rgb.m_g)
		hsv.m_h = 85 + (unsigned int)43 * (rgb.m_b - rgb.m_r) / (rgbMax - rgbMin);
	else
		hsv.m_h = 171 + (unsigned int)43 * (rgb.m_r - rgb.m_g) / (rgbMax - rgbMin);

	return hsv;
}
