#ifndef FINAL_PROJECT_ELEMENT_INTERFACES_H
#define FINAL_PROJECT_ELEMENT_INTERFACES_H

#include "types.h"
#include "point.h"
#include "cinder/gl/gl.h"

using glm::vec2;

namespace finalproject {
namespace elements {

    class Shape {
    public:
        void drawSquare(size_t row, size_t col, ci::Color color) const {
            ci::gl::color(color);
            glm::vec2 pixel_top_left = top_left_corner_ + vec2(col * pixel_side_length_, row * pixel_side_length_);
            glm::vec2 pixel_bottom_right = pixel_top_left + vec2(pixel_side_length_, pixel_side_length_);
            ci::Rectf pixel_bounding_box(pixel_top_left, pixel_bottom_right);
            ci::gl::drawSolidRect(pixel_bounding_box);
        }

        void drawCircle(size_t row, size_t col, ci::Color color, float radius) const {
            ci::gl::color(color);
            glm::vec2 pixel_top_left = top_left_corner_ + vec2(col * pixel_side_length_, row * pixel_side_length_);
            glm::vec2 pixel_bottom_right = pixel_top_left + vec2(pixel_side_length_, pixel_side_length_);
            glm::vec2 center = midPoint(pixel_top_left, pixel_bottom_right);
            ci::gl::drawSolidCircle(center, radius);
        }

        glm::vec2 midPoint(glm::vec2 p1, glm::vec2 p2) const {
            return glm::vec2((p1.x + p2.x) /2,(p1.y + p2.y) /2) ;
        }

    protected:
        double pixel_side_length_ = (Configuration::WINDOW_SIZE - 2 * Configuration::WINDOW_MARGIN) / Configuration::GRID_SIZE;
        glm::vec2 top_left_corner_ = glm::vec2(Configuration::WINDOW_MARGIN, Configuration::WINDOW_MARGIN);
    };

    /**
     * An interface that represents the parts of the Pacman game that do not move.
     * This includes the walls, the coins, and the dots.
     */
    class StaticElement : public Shape {
    public:

        virtual void draw(size_t row, size_t col) const = 0;

    };

    /**
     * An interface that represents the parts of the Pacman game that do move.
     * This includes the Pacman and the ghosts
     */
    class DynamicElement : public Shape {
    public:

        virtual void draw() const = 0;

        Point getPosition() const {
            return position_;
        }

        void setPosition(size_t x, size_t y) {
            position_.setX(x);
            position_.setY(y);
        }

        Direction getDirection() const {
            return direction_;
        }

        void setDirection(Direction direction) {
            direction_ = direction;
        }

    protected:
        Point position_;
        Direction direction_;
    };
}
}

#endif //FINAL_PROJECT_ELEMENT_INTERFACES_H