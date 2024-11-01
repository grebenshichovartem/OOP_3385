all: Play

Play: main.o GameField.o ShipManager.o Ship.o ShipSegment.o GameStatus.o AbilityManager.o BarrageAbility.o DoubleDamageAbility.o ScannerAbility.o
	g++  main.o GameField.o ShipManager.o Ship.o ShipSegment.o GameStatus.o AbilityManager.o BarrageAbility.o DoubleDamageAbility.o ScannerAbility.o -o play
main.o: main.cpp 
	g++ -c main.cpp
ShipManager.o: ShipManager.cpp ShipManager.h 
	g++ -c ShipManager.cpp
Ship.o: Ship.cpp Ship.h CustomExceptions.h
	g++ -c Ship.cpp 
ShipSegment.o: ShipSegment.cpp ShipSegment.h 
	g++ -c ShipSegment.cpp
GameStatus.o: GameStatus.cpp GameStatus.h
	g++ -c GameStatus.cpp
GameField.o: GameField.cpp GameField.h CustomExceptions.h
	g++ -c GameField.cpp	
AbilityManager.o: AbilityManager.cpp AbilityManager.h Ability.h CustomExceptions.h
	g++ -c AbilityManager.cpp
BarrageAbility.o: BarrageAbility.cpp BarrageAbility.h CustomExceptions.h
	g++ -c BarrageAbility.cpp
DoubleDamageAbility.o: DoubleDamageAbility.cpp DoubleDamageAbility.h CustomExceptions.h
	g++ -c DoubleDamageAbility.cpp
ScannerAbility.o: ScannerAbility.cpp ScannerAbility.h
	g++ -c ScannerAbility.cpp
clean: 
	Remove-Item *.o -Force
	
