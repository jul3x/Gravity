//
// Created by jprolejko on 10.06.19.
//

#ifndef GRAVITY_OBJECTS_BACKGROUND_H
#define GRAVITY_OBJECTS_BACKGROUND_H


#include <objects/Star.h>


class Background : public sf::Drawable {
public:
    Background();

    void update(float time_elapsed);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    const sf::Color background_color_;
    std::vector<Star> stars_;
};


#endif //GRAVITY_OBJECTS_BACKGROUND_H