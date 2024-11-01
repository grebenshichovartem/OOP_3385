#include "CustomExceptions.h"

GameFieldException::GameFieldException(const char* message) : runtime_error(message) {}

ShipManagerException::ShipManagerException(const char* message) : runtime_error(message) {}

AbilityManagerException::AbilityManagerException(const char* message) : runtime_error(message) {}