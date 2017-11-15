#include "S.h"
#include "mingw.mutex.h"


namespace S {
    sf::Font font;

    sf::Clock secondFrameClock;
    std::mutex mutex;

    std::map<int, std::vector<Node *>> nodes;
    std::map<int, sf::Clock> threadFrameTimes;
    std::map<int, int> threadUPS;
    std::map<int, int> threadCompletance;


    int nextThread = 0;

    sf::RenderWindow *window;
    int concurrency = std::thread::hardware_concurrency();


    int FPS;

    void add(Node *node) {
        nodes[nextThread].push_back(node);
        nextThread = nextThread == (concurrency - 1) ? 0 : nextThread + 1;
    }

    void refresh(int &threadIndex) {
        while (window->isOpen()) {
            mutex.lock();
//            if (threadCompletance[threadIndex] == 0) {
                auto frameTime = threadFrameTimes[threadIndex].getElapsedTime().asMilliseconds();
                threadFrameTimes[threadIndex].restart();

                for (auto &n:nodes[threadIndex]) {
                    n->update(frameTime, threadIndex);
                    threadUPS[threadIndex]++;
                }

                threadCompletance[threadIndex] = 1;
//            }
            mutex.unlock();
        }
    }

    bool threadsReady() {
        int i = 0;
        for (auto &t:threadCompletance) {
            i = t.second == 1 ? i + 1 : i;
        }

        return i == concurrency;
    }

    void resetThreads() {
        for (int i = 0; i < concurrency; ++i) {
            threadCompletance[i] = 0;
        }
    }

    void redraw() {
        for (int i = 0; i < concurrency; ++i) {
            if (!nodes[i].empty()) {
                for (auto &n:nodes[i]) {
                    n->draw();
                }
            }
        }
    }
}