#ifndef SCREENMANAGER_HPP
#define SCREENMANAGER_HPP

#include <iostream>
#include <map>
#include "gameplay/screens/screen.hpp"

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