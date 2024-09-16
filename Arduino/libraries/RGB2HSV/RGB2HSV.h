#ifndef RGB2HSV_h
#define RGB2HSV_h

/*! RGB color representation. */
struct RgbColor {
	RgbColor() {}
	RgbColor(unsigned char r, unsigned char g, unsigned char b) :
		m_r(r), m_g(g), m_b(b)
	{}

	unsigned char m_r = 255;
	unsigned char m_g = 255;
	unsigned char m_b = 255;
};


/*! Holds HsvColor but with hue value in range of 0-255, instead of 0-359. */
struct HsvColor {
	HsvColor() {}
	HsvColor(unsigned char h, unsigned char s, unsigned char v) :
		m_h(h), m_s(s), m_v(v)
	{}
	
	unsigned int m_h = 255; // range is 0-255, not as usual 0 - 360
	unsigned char m_s = 255;
	unsigned char m_v = 255;
};


RgbColor HsvToRgb(HsvColor hsv);
HsvColor RgbToHsv(RgbColor rgb);


#endif // RGB2HSV_h
