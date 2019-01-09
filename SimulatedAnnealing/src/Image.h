//
// Created by Khyber on 9/29/2018.
//

#ifndef IMAGE_H
#define IMAGE_H

#include "Rectangle.h"

class Image {
    
    using ImageImpl = Rectangle<bool>; // TODO

private:
    
    ImageImpl impl;
    
public:
    
    Image(double x, double y, double width, double height) {
        impl = {.x = x, .y = y, .width = width, .height = height, .data = true};
    }
    
    ImageImpl get() {
        return impl;
    }
    
    Rectangle<const Image&> toRectangle() {
        return {.x = impl.x, .y = impl.y, .width = impl.width, .height = impl.height, .data = *this};
    }
    
};

#endif // IMAGE_H
