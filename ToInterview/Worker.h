//
// Created by Елена on 06.01.2020.
//

#ifndef TOINTERVIEW_WORKER_H
#define TOINTERVIEW_WORKER_H

#include <boost/lockfree/queue.hpp>
#include <boost/thread/thread.hpp>
#include "Request.h"
#include <thread>
#include <vector>

struct Worker {

    void run(int time) {
        std::thread temp(&Worker::addingTasks, this);
        for (int i = 0; i < count_threads; i++) {
            threads.emplace_back(&Worker::runWorker, this);
        }
        sleep(time);
        stopAll();
        temp.join();
        while (!q.empty()) {
            Request *req;
            q.pop(req);
            std::cout << " [ cancelled ] " << req->identifier << "\n";
            delete req;
        }
    }

    Worker(unsigned long numb_of_treads) : count_threads(numb_of_treads){}

private:
    boost::lockfree::queue<Request *> q{1};
    std::vector<std::thread> threads;
    unsigned long count_threads = 2;
    Stopper stopper;

    void addingTasks() {
        while (!stopper.wasStopped()) {
            Request *request = GetRequest(stopper);
            if (request != nullptr) {
                q.push(request);
            }
        }
    }

    void runWorker() {
        while (!stopper.wasStopped()) {
            Request *request;
            if (q.pop(request)) {
                ProcessRequest(request, stopper);
                delete request;
            }
        }
    }

    void stopAll() {
        stopper.stop();
        for (int i = 0; i < count_threads; ++i) {
            if (threads[i].joinable()) {
                threads[i].join();
            }
        }
    }

};

#endif //TOINTERVIEW_WORKER_H