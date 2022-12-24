#!/bin/bash
echo -e "\e[1;32m${bold}Installing needed packages...\e[0m" && sudo apt -y install bash clang libglut-dev libglew-dev pkgconf
sleep 5s
if [ -d build ]
then
	sleep 1s
else
	mkdir build
fi
if [ -f ./build/ElectroMark ]
then
	rm ./build/ElectroMark
fi
echo -e "\e[1;32m${bold}Compilling and executing...\e[0m"
clang++ ./src/main.cpp -o ./build/ElectroMark -mfp64 -mlong-double-128 $(pkg-config --cflags --libs glut glu glew) -v 
if [ -f ./build/ElectroMark ]
then
	chmod u+w+x ./build/ElectroMark && chmod 777 ./build/ElectroMark && ./build/ElectroMark
else
	echo -e "\e[1;31m${bold}Errors occured ! Please see output above.\e[0m"
fi
