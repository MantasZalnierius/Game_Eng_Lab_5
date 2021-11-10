CXX			:= g++
CXXFLAGS 	:= -std=c++11 -Wall -Wextra -Werror -g -I.

MSG_START	:= "Build Started"
MSG_END		:= "Build Complete"
MSG_CLEAN	:= "Cleaning up"

BUILD_DIR	:= ./bin
SRC_DIR		:= ./src

lib			:= "C:/SDL2-devel-2.0.16-VC/SDL2-2.0.16/lib/"
include		:= "C:/SDL2-devel-2.0.16-VC/SDL2-2.0.16/include"

SRC			:= ./src/*.cpp ./src/Systems/*.cpp

all			:= build

build:
	@echo ${MSG_START}
	${CXX} -o TestFile ${SRC} -I${include} -I. -I./include -L${lib} -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image
	@echo ${MSG_END}