#include "observer.hpp"
#include <iostream>

FileObserver::FileObserver() {
    log_file.open("log.txt", std::ios::app);
}

FileObserver::~FileObserver() {
    if (log_file.is_open()) {
        log_file.close();
    }
}

void FileObserver::Update(const std::string& mes) {
    if (log_file.is_open()) {
        log_file << mes << std::endl;
    }
}

void ConsoleObserver::Update(const std::string& mes) {
    std::cout << "BATTLE " << mes << std::endl;
}