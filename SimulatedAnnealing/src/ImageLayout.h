//
// Created by Khyber on 9/29/2018.
//

#ifndef RECTANGLES_H
#define RECTANGLES_H

#include <vector>
#include <algorithm>
#include "SimulatedAnnealing.h"
#include "Rectangle.h"

template <typename Image>
class ImageLayout {
    
    using _Rectangle = Rectangle<const Image&>;
    using Rectangles = std::vector<const _Rectangle>;
    using Images = std::vector<const Image&>;

private:
    
    const _Rectangle bounds;
    const size_t numRectangles;
    Rectangles originalRectangles;
    Rectangles randomRectangles;
    Rectangles rectangles;
    Rectangles prevRectangles;
    
    double emptyArea(const _Rectangle& bounds) const {
        double emptyArea = bounds.area();
        for (const _Rectangle& rectangle : rectangles) {
            emptyArea -= rectangle.area();
        }
        return emptyArea;
    }
    
    /**
     * Finds the smallest bounding rectangle of everything in rectangles
     * @return smallest bounding rectangle
     */
    const _Rectangle& minBounds() const {
        double x = 0;
        double y = 0;
        double x2 = 0;
        double y2 = 0;
        for (const _Rectangle& rectangle : rectangles) {
            if (rectangle.x > x) {
                x = rectangle.x;
            }
            if (rectangle.y > y) {
                y = rectangle.y;
            }
            if (rectangle.x2() > x2) {
                x2 = rectangle.x2();
            }
            if (rectangle.y2() > y2) {
                y2 = rectangle.y2();
            }
        }
        return _Rectangle {.x = x, .y = y, .width = x2 - x, .height = y2 - y};
    }
    
    template <typename Generator>
    void shuffle(Generator& generator) {
        randomRectangles = originalRectangles;
        std::shuffle(randomRectangles.begin(), randomRectangles.end(), generator);
    }
    
    /**
     * Attempts to layout all of Rectangles in randomRectangles into rectangles.
     */
    void doLayout() {
        rectangles.clear();
        for (const _Rectangle& rectangle : randomRectangles) {
            _Rectangle r = rectangle;
            rectangles.push_back(r);
        }
    }

public:
    
    ImageLayout(const Image& bounds, const Images& images)
            : bounds(bounds.toRectangle()), numRectangles(images.size()) {
        originalRectangles.reserve(numRectangles);
        randomRectangles.reserve(numRectangles);
        this->rectangles.reserve(numRectangles);
        prevRectangles.reserve(numRectangles);
        
        for (const Image& image : images) {
            originalRectangles.push_back(image.toRectangle());
        }
    }
    
    const Rectangles& original() {
        return originalRectangles;
    }
    
    const Rectangles& layout() {
        return rectangles;
    }
    
    /**
     * If not all rectangles fit in bounds, return empty area left.
     * If all rectangles do fit, construct a smaller bounds.
     *
     * @return empty area
     */
    double energy() const {
        return emptyArea(rectangles.size() < numRectangles ? bounds : minBounds());
    }
    
    template <typename Generator>
    void move(Generator& generator) {
        prevRectangles = rectangles;
        shuffle(generator);
        doLayout();
    }
    
    void undo() {
        rectangles = prevRectangles;
    }
    
    template <typename Temperature, typename Generator>
    const Rectangles& anneal(const size_t numIterations, Temperature& temperature, Generator& generator) {
        if (numRectangles <= 1) {
            return originalRectangles;
        }
        return SA::anneal(*this, numIterations, temperature, generator).layout();
    }
    
    template <typename Temperature, typename Generator>
    static const Rectangles& anneal(const Image& bounds, const Images& images,
                                         const size_t numIterations, Temperature& temperature, Generator& generator) {
        return ImageLayout(bounds, images).anneal(numIterations, temperature, generator);
    };
    
};

#endif // RECTANGLES_H
