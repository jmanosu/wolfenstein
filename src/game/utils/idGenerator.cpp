#include "idGenerator.hpp"

IdGenerator * IdGenerator::mInstance = nullptr;

IdGenerator * IdGenerator::instance()
{
    if (mInstance == nullptr) {
        mInstance = new IdGenerator();
    }
    return mInstance;
}

void IdGenerator::release()
{
    delete mInstance;
}


IdGenerator::IdGenerator()
{
    mId = 0;
}

IdGenerator::~IdGenerator()
{
}

int IdGenerator::generateId()
{
    mId++;
    return mId;
}

