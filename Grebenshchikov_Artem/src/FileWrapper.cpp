#include "FileWrapper.h"
#include "GameEntities.h"
#include <sstream>
#include "BattleshipException.h"



FileWrapper::FileWrapper(const std::string &filename) {
    file.open(filename, std::ios::in | std::ios_base::out);
    if (!file) {
        throw FileException("Ошибка открытия файла" + filename);
    }
}


FileWrapper::~FileWrapper() {
    file.close();
}


void FileWrapper::write(const std::string& newState, const std::shared_ptr<GameEntities>& entities) {
    if (!file.is_open()) {
        throw FileException("Файл не открыт");
    }
    try {
        file << newState << " " << *entities;
    } catch (const LoadInFileException& e) {
        std::cerr << "Ошибка записи в файл: " << e.what() << std::endl;
        throw;
    }
}

void FileWrapper::read(std::string& newState, std::shared_ptr<GameEntities>& entities) {
    if (!file.is_open()) {
        throw FileException("Файл не открыт");
    }
    try {
        file >> newState >> *entities;
    } catch (const LoadInFileException& e) {
        std::cerr << "Ошибка чтения из файла: " << e.what() << std::endl;
        throw;
    }
}