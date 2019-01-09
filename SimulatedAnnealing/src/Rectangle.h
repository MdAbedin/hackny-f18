//
// Created by Khyber on 9/29/2018.
//

#ifndef RECTANGLE_H
#define RECTANGLE_H

template <typename Data>
struct Rectangle {
    
    double x;
    double y;
    double width;
    double height;
    
    const Data data;
    
    double area() const {
        return width * height;
    }
    
    double x2() const {
        return x + width;
    }
    
    double y2() const {
        return y + height;
    }
    
};

#endif // RECTANGLE_H
