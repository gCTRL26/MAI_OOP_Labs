#pragma once

#include <fstream>
#include <string>

class Observer {
  public:
    virtual void Update(const std::string& mes) = 0;
    virtual ~Observer() = default;
};

class FileObserver : public Observer {
  private:
    std::ofstream log_file;
  public:
    FileObserver();
    ~FileObserver();
    void Update(const std::string& mes) override;
};

class ConsoleObserver : public Observer {
  public:
    void Update(const std::string& mes) override;
};
