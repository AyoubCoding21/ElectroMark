#!/bin/bash
echo -e "\e[1;32m${bold}Installing needed packages...${normal} \e[0m" && sudo apt -y install clang libglut-dev libglew-dev bash ld pkgconf &> /dev/null
sleep 1s
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
echo -e "\e[1;32m${bold}Compilling and executing...${normal} \e[0m"
clang++ ./src/main.cpp -o ./build/ElectroMark -mfp64 -mlong-double-128 -DFREEGLUT_STATIC -L/usr/lib64 -lGLEW -lGL -lX11 -lGLU -lglut
if [ -f ./build/ElectroMark ]
then
	./build/ElectroMark
else
	echo -e "\e[1;31m${bold}Errors occured ! Please see output above.${normal} \e[0m"
fi
