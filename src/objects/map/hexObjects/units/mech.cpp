#include "mech.hpp"

Mech::Mech() :
    mIdleTexture(nullptr)
{
    AnimatedTexture temp("hexObjects/Mech2Animated.png", 0, 0, 25, 27, 4, 500, AnimatedTexture::horizontal);
    temp.setColor(255,0,0,255);
    setIdleTexture(&temp);
    this->pos(GVector(3,-7));
    mWeapon = new Weapon();
    mHealth = 5;
}

Mech::~Mech()
{
    delete mIdleTexture;
}

void Mech::update() 
{
    if (mIdleTexture != nullptr) {
        mIdleTexture->update();
    }
}

void Mech::render()
{
    if (mIdleTexture != nullptr) {
        mIdleTexture->render();
    }
}

void Mech::setIdleTexture(const AnimatedTexture * idleTexture)
{
    AnimatedTextureUtils::copy(idleTexture, mIdleTexture);
    mIdleTexture->parent(this);
}


void Mech::applyWeapon(Weapon * weapon)
{
    std::cout << weapon->getName() << std::endl;
    
    if (mHealth > 0) {
        mHealth--;
        std::cout << "big OUCH!" << std::endl;
    } else {
        std::cout << "you sunk my battleship" << std::endl;
    }
}