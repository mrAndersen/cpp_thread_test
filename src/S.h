#ifndef THREAD_TEST_S_H
#define THREAD_TEST_S_H

#include <map>
#include <Graphics/Font.hpp>
#include "Node.h"
#include "mingw.thread.h"
#include "mingw.mutex.h"

class Node;

namespace S {
    extern sf::Font font;

    extern sf::Clock secondFrameClock;
    extern std::mutex mutex;

    extern std::map<int, std::vector<Node *>> nodes;
    extern std::map<int, sf::Clock> threadFrameTimes;
    extern std::map<int, int> threadUPS;
    extern std::map<int, int> threadCompletance;

    extern int nextThread;

    extern sf::RenderWindow *window;
    extern int concurrency;

    extern int FPS;

    void add(Node *node);
    void refresh(int &threadIndex);
    void redraw();
    bool threadsReady();
    void resetThreads();
}

#endif //THREAD_TEST_S_H
