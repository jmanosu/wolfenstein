#ifndef IDGENERATOR
#define IDGENERATOR

#include <set>

class IdGenerator
{
    public:
        static IdGenerator * instance();
        static void release();

        int generateId();
    private:
        IdGenerator();
        ~IdGenerator();

        int mId;

        static IdGenerator * mInstance;
//        std::set<unsigned int> mIds;
};

#endif