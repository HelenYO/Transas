//
// Created by Елена on 06.01.2020.
//

#ifndef TOINTERVIEW_REQUEST_H
#define TOINTERVIEW_REQUEST_H

#include <zconf.h>
#include "Stopper.h"

std::mutex mutex;
static unsigned counter = 1;

struct Request {
    Request(int identifier) : identifier(identifier) {}

    int identifier;
};

Request *GetRequest(Stopper stopSignal) {
    if (stopSignal.wasStopped()) {
        return nullptr;
    }
    /**
     * симуляция ожидания
     */
    sleep(1);

    std::lock_guard<std::mutex> lock(mutex);
    Request *req = new Request(counter);
    std::cout << "[request] " << counter++ << std::endl;
    return req;
};

void ProcessRequest(Request *request, Stopper stopSignal) {
    /**
     * симуляция процесса
     */
    int i = 0;
    int c = rand();
    while (i < c) {
        i++;
    }

    std::lock_guard<std::mutex> lock(mutex);
    std::cout << request->identifier << " [in process] \n";
};

#endif //TOINTERVIEW_REQUEST_H
