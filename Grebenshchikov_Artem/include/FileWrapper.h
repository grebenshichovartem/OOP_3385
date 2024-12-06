#ifndef OOP_FILE_WRAPPER_H
#define OOP_FILE_WRAPPER_H

#include <fstream>
#include "GameEntities.h"



class FileWrapper {
private:
    std::fstream file;

public:
    explicit FileWrapper(const std::string &filename);
    ~FileWrapper();
    void read(std::string& newState, std::shared_ptr<GameEntities>& entities);
    void write(const std::string& newState, const std::shared_ptr<GameEntities>& entities);
};


#endif