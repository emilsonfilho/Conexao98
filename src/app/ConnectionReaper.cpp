//
// Created by Emilson Filho on 08/03/2026.
//

#include "ConnectionReaper.h"

#include <iostream>
#include <mutex>
#include <chrono>

ConnectionReaper::ConnectionReaper() {
    isServerActive = true;

    cleanupThread = std::thread([this]() -> void {
        this->cleanupLoop();
    });
}

ConnectionReaper::~ConnectionReaper() {
    isServerActive = false;
    queueCondition.notify_all();
    cleanupThread.join();
}

void ConnectionReaper::moveToGraveyard(std::unique_ptr<UserSession> deadSession) {
    std::lock_guard<std::mutex> lock(queueMutex);
    cleanupQueue.push(std::move(deadSession));
    queueCondition.notify_one();
}

void ConnectionReaper::cleanupLoop() {
    while (isServerActive) {
        std::unique_lock<std::mutex> lock(queueMutex);
        queueCondition.wait_for(lock, std::chrono::seconds(1), [&]() -> bool {
            return !cleanupQueue.empty() || !isServerActive;
        });

        while (!cleanupQueue.empty()) {
            std::unique_ptr<UserSession> session = std::move(cleanupQueue.front());
            cleanupQueue.pop();

            std::cout << "Connection limpada!\n";
        }
    }
}
