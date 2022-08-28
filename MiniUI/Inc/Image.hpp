
#ifndef __IMAGE_HPP
#define __IMAGE_HPP

#include "Color.hpp"

class Image {
public:
    signed short Width;
    signed short Height;
    Color Data[];
};

#endif // __IMAGE_HPP
