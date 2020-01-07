#ifndef SCREENMANAGER
#define SCREENMANAGER

#include <iostream>
#include <map>
#include "screens/screen.hpp"

class ScreenManager {
    public:
        ScreenManager();
        ~ScreenManager();
        static ScreenManager * instance();
        static void release();

        void addScreen(std::string, Screen *);
        void setCurrentScreen(std::string);
        void render();
        void update();

    private:
        static ScreenManager * sInstance;
        std::map<std::string, Screen *> mScreens;

        Screen * mActiveScreen;

    
};

#endif