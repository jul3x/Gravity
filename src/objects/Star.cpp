//
// Created by jprolejko on 12.06.19.
//


#include <Config.h>

#include <objects/Star.h>

void Star::update(float time_elapsed) {
    // alpha change
    static float change_direction = ALPHA_CHANGE_VELOCITY_;
    if (this->getTransparency() >= 255 || this->getTransparency() <= 0) 
    {
        change_direction = -change_direction;
    }
    
    this->setTransparency(this->getTransparency() + static_cast<int>(change_direction * time_elapsed));
    this->setPosition(this->getPosition() + time_elapsed * velocity_);

    // infinite loop of movement
    if ((this->getPosition().x - this->getRadius() * Config::OBJECT_ZOOM_) * Config::PIXELS_PER_KM_ > Config::WINDOW_WIDTH_PIXELS_)
    {
        this->setPosition(- this->getRadius() * Config::OBJECT_ZOOM_, this->getPosition().y);
    }

    if ((this->getPosition().y - this->getRadius() * Config::OBJECT_ZOOM_) * Config::PIXELS_PER_KM_ > Config::WINDOW_HEIGHT_PIXELS_)
    {
        this->setPosition(this->getPosition().x, - this->getRadius() * Config::OBJECT_ZOOM_);
    }
}