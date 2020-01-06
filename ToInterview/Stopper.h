//
// Created by Елена on 06.01.2020.
//

#ifndef TOINTERVIEW_STOPPER_H
#define TOINTERVIEW_STOPPER_H

#include <memory>

struct Stopper {

    void stop(){
        *toStop = true;
    }

    bool wasStopped(){
        return *toStop;
    }

    Stopper(): toStop(std::make_shared<std::atomic_bool>(false)){}

private:
    std::shared_ptr<std::atomic_bool> toStop;
};

#endif //TOINTERVIEW_STOPPER_H
