
#ifndef __MINIUI_COLOR_H
#define __MINIUI_COLOR_H

#include <stdint.h>

#if defined(MINIUI_RGB888)
    #define MINIUI_RGB_STRUCT           struct {                    \
                                        public:                     \
                                            const uint8_t R;        \
                                            const uint8_t G;        \
                                            const uint8_t B;        \
                                        }
    #define MINIUI_R_VALUE(value)       (value)
    #define MINIUI_G_VALUE(value)       (value)
    #define MINIUI_B_VALUE(value)       (value)
    #define MINIUI_RGB_INIT(r, g, b)    R(MINIUI_R_VALUE(r)), G(MINIUI_G_VALUE(g)), B(MINIUI_B_VALUE(b))
#elif defined(MINIUI_BGR888)
    #define MINIUI_RGB_STRUCT           struct {                    \
                                        public:                     \
                                            const uint8_t B;        \
                                            const uint8_t G;        \
                                            const uint8_t R;        \
                                        }
    #define MINIUI_R_VALUE(value)       (value)
    #define MINIUI_G_VALUE(value)       (value)
    #define MINIUI_B_VALUE(value)       (value)
    #define MINIUI_RGB_INIT(r, g, b)    B(MINIUI_B_VALUE(b)), G(MINIUI_G_VALUE(g)), R(MINIUI_R_VALUE(r))
#elif defined(MINIUI_RGB555)
    #define MINIUI_RGB_STRUCT           struct {                    \
                                        public:                     \
                                            const uint16_t R : 5;   \
                                            const uint16_t G : 5;   \
                                            const uint16_t B : 5;   \
                                        }
    #define MINIUI_R_VALUE(value)       ((value) >> 3)
    #define MINIUI_G_VALUE(value)       ((value) >> 3)
    #define MINIUI_B_VALUE(value)       ((value) >> 3)    
    #define MINIUI_RGB_INIT(r, g, b)    R(MINIUI_R_VALUE(r)), G(MINIUI_G_VALUE(g)), B(MINIUI_B_VALUE(b))
#elif defined(MINIUI_RGB565)
    #define MINIUI_RGB_STRUCT           struct {                    \
                                        public:                     \
                                            const uint16_t R : 5;   \
                                            const uint16_t G : 6;   \
                                            const uint16_t B : 5;   \
                                        }
    #define MINIUI_R_VALUE(value)       ((value) >> 3)
    #define MINIUI_G_VALUE(value)       ((value) >> 2)
    #define MINIUI_B_VALUE(value)       ((value) >> 3)    
    #define MINIUI_RGB_INIT(r, g, b)    R(MINIUI_R_VALUE(r)), G(MINIUI_G_VALUE(g)), B(MINIUI_B_VALUE(b))
#else
    #error "Please define the screen's color system"
#endif

class RgbColor {
public:
    MINIUI_RGB_STRUCT;

    RgbColor(void);
    RgbColor(uint32_t rgb);
    RgbColor(uint8_t r, uint8_t g, uint8_t b);

    void operator=(const RgbColor &color);
};

class Color {
public:
    union {
    public:
        RgbColor RGB;
        struct {
        public:
            MINIUI_RGB_STRUCT;
            const uint8_t A;
        };
    };

    Color(void);
    Color(uint32_t argb);
    Color(uint8_t r, uint8_t g, uint8_t b);
    Color(uint8_t a, uint8_t r, uint8_t g, uint8_t b);
    Color(const Color &color);

    void operator=(const Color &color);

    bool operator==(const Color &color);
    bool operator!=(const Color &color);

    static const Color Black;
    static const Color Silver;
    static const Color Gray;
    static const Color White;
    static const Color Maroon;
    static const Color Red;
    static const Color Purple;
    static const Color Fuchsia;
    static const Color Green;
    static const Color Lime;
    static const Color Olive;
    static const Color Yellow;
    static const Color Navy;
    static const Color Blue;
    static const Color Teal;
    static const Color Aqua;
    static const Color Orange;
    static const Color AliceBlue;
    static const Color AntiqueWhite;
    static const Color Aquamarine;
    static const Color Azure;
    static const Color Beige;
    static const Color Bisque;
    static const Color BlanchedAlmond;
    static const Color BlueViolet;
    static const Color Brown;
    static const Color Burlywood;
    static const Color CadetBlue;
    static const Color Chartreuse;
    static const Color Chocolate;
    static const Color Coral;
    static const Color CornflowerBlue;
    static const Color Cornsilk;
    static const Color Crimson;
    static const Color Cyan;
    static const Color DarkBlue;
    static const Color DarkCyan;
    static const Color DarkGoldenrod;
    static const Color DarkGray;
    static const Color DarkGreen;
    static const Color DarkGrey;
    static const Color DarkKhaki;
    static const Color DarkMagenta;
    static const Color DarkOliveGreen;
    static const Color DarkOrange;
    static const Color DarkOrchid;
    static const Color DarkRed;
    static const Color DarkSalmon;
    static const Color DarkSeaGreen;
    static const Color DarkSlateBlue;
    static const Color DarkSlateGray;
    static const Color DarkSlateGrey;
    static const Color DarkTurquoise;
    static const Color DarkViolet;
    static const Color DeepPink;
    static const Color SeepSkyBlue;
    static const Color DimGray;
    static const Color DimGrey;
    static const Color DodgerBlue;
    static const Color Firebrick;
    static const Color FloralWhite;
    static const Color ForestGreen;
    static const Color Gainsboro;
    static const Color GhostWhite;
    static const Color Gold;
    static const Color Goldenrod;
    static const Color GreenYellow;
    static const Color Grey;
    static const Color Honeydew;
    static const Color HotPink;
    static const Color IndianRed;
    static const Color Indigo;
    static const Color Ivory;
    static const Color Khaki;
    static const Color Lavender;
    static const Color LavenderBlush;
    static const Color LawnGreen;
    static const Color LemonChiffon;
    static const Color LightBlue;
    static const Color LightCoral;
    static const Color LightCyan;
    static const Color LightGoldenrodYellow;
    static const Color LightGray;
    static const Color LightGreen;
    static const Color LightGrey;
    static const Color LightPink;
    static const Color LightSalmon;
    static const Color LightSeaGreen;
    static const Color LightSkyBlue;
    static const Color LightSlateGray;
    static const Color LightSlateGrey;
    static const Color LightSteelBlue;
    static const Color LightYellow;
    static const Color LimeGreen;
    static const Color Linen;
    static const Color Magenta;
    static const Color MediumAquamarine;
    static const Color MediumBlue;
    static const Color MediumOrchid;
    static const Color MediumPurple;
    static const Color MediumSeaGreen;
    static const Color MediumSlateBlue;
    static const Color MediumSpringGreen;
    static const Color MediumTurquoise;
    static const Color MediumVioletRed;
    static const Color MidnightBlue;
    static const Color MintCream;
    static const Color MistyRose;
    static const Color Moccasin;
    static const Color NavajoWhite;
    static const Color OldLace;
    static const Color OliveDrab;
    static const Color OrangeRed;
    static const Color Orchid;
    static const Color PaleGoldenrod;
    static const Color PaleGreen;
    static const Color PaleTurquoise;
    static const Color PaleVioletRed;
    static const Color PapayaWhip;
    static const Color PeachPuff;
    static const Color Peru;
    static const Color Pink;
    static const Color Plum;
    static const Color PowderBlue;
    static const Color RosyBrown;
    static const Color RoyalBlue;
    static const Color SaddleBrown;
    static const Color Salmon;
    static const Color SandyBrown;
    static const Color SeaGreen;
    static const Color SeaShell;
    static const Color Sienna;
    static const Color SkyBlue;
    static const Color SlateBlue;
    static const Color SlateGray;
    static const Color Snow;
    static const Color SpringGreen;
    static const Color SteelBlue;
    static const Color Tan;
    static const Color Thistle;
    static const Color Tomato;
    static const Color Turquoise;
    static const Color Violet;
    static const Color Wheat;
    static const Color WhiteSmoke;
    static const Color YellowGreen;
    static const Color Transparent;
};

#endif /* __MINIUI_COLOR_H */
