//
// Created by ganz on 28/07/17.
//

#include <iostream>
#include <ncurses.h>
#include "CursesRender.hpp"
#include "log.hpp"
//
//extern "C" fender::CursesRender* createCursesRenderer()
//{
//    return new fender::CursesRender();
//}
//
//fender::CursesRender::CursesRender()
//{
//
//}
//
//void    fender::CursesRender::openWindow()
//{
//    initscr();
//    noecho();
//    noraw();
//}
//
//void    fender::CursesRender::refresh()
//{
//    ::refresh();
//}
//
//void    fender::CursesRender::write(int x, int y, std::string const &msg)
//{
//    mvprintw(x, y, msg.c_str());
//}
//
//void    fender::CursesRender::closeWindow(void)
//{
//    endwin();
//}