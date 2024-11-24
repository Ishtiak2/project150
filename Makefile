.PHONY: task1 task2 task3

task1:
	g++ -o task1 task1.cpp -F/Library/Frameworks/ -framework SDL2
	./task1

task2:
	g++ -o task2 task2.cpp -F/Library/Frameworks/ -framework SDL2
	./task2

task3:
	g++ -o task3 task3.cpp -F/Library/Frameworks/ -framework SDL2
	./task3
