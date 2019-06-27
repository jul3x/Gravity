//
// Created by jprolejko on 10.06.19.
//

#ifndef GRAVITY_OBJECTS_BACKGROUND_H
#define GRAVITY_OBJECTS_BACKGROUND_H

#include <list>

#include <objects/Star.h>


class Background : public AbstractPhysicalObject {
public:
    Background();

    virtual float getMass() const;
    void update(float time_elapsed);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    static constexpr int NUMBER_OF_STARS_ = 200;

    std::list<Star> stars_;
};


#endif //GRAVITY_OBJECTS_BACKGROUND_H