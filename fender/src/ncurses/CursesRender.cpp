//
// Created by ganz on 28/07/17.
//

#include <iostream>
#include <ncurses.h>
#include "CursesRender.hpp"
#include "flog.hpp"

extern "C" fender::CursesRender* createCursesRenderer(std::string const &config)
{
    return new fender::CursesRender(config);
}

fender::CursesRender::CursesRender(std::string const &configFile)
{
    LOUT("Ncurses Render parsing " + configFile);
}

void    fender::CursesRender::openWindow(int x, int y)
{
    initscr();
    noecho();
    noraw();
}

void    fender::CursesRender::refresh()
{
    ::refresh();
}

void    fender::CursesRender::write(int x, int y, std::string const &msg)
{
    mvprintw(x, y, msg.c_str());
}

void    fender::CursesRender::closeWindow(void)
{
    endwin();
}