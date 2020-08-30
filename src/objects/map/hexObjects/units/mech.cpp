#include "mech.hpp"

Mech::Mech() : Unit(),
    mIdleTexture(nullptr),

    _defaultTexture(nullptr),
    _submergedTexture(nullptr),

    _defaultHighlightTexture(nullptr),
    _submergedHighlightTexture(nullptr)
{
    _defaultTexture = new AnimatedTexture("hexObjects/Mech2Animated.png", 0, 0, 25, 27, 4, 500, AnimatedTexture::horizontal);
    _defaultTexture->parent(this);
    _defaultTexture->pos(GVector(3,-7));
    
    _submergedTexture = new Texture("hexObjects/Mech2Animated.png", 0, 27, 25, 27);
    _submergedTexture->parent(this);
    _submergedTexture->pos(GVector(3,0));

    _defaultGameStats._health = 5;
    _defaultGameStats._moveRange = 3;
    _defaultGameStats._moveCount = 3;

    reset();
}

Mech::~Mech()
{
    delete mIdleTexture;
}

void Mech::update() 
{
    if (_hex == nullptr || _hex->getType() != BattleHex::BattleHexType::water) {
        _defaultTexture->update();
    }
}

void Mech::render()
{
    if (_hex != nullptr && _hex->getType() == BattleHex::BattleHexType::water) {
        _submergedTexture->render();
    } else {
        _defaultTexture->render();
    }
}

void Mech::setIdleTexture(const AnimatedTexture * idleTexture)
{
    AnimatedTextureUtils::copy(idleTexture, mIdleTexture);
    mIdleTexture->parent(this);
}


void Mech::applyWeapon(Weapon * weapon)
{
    if (_currentGameStats._health > 0) {
        _currentGameStats._health--;
        std::cout << "big OUCH!" << std::endl;
    } else {
        std::cout << "you sunk my battleship" << std::endl;
    }
}