cmake_minimum_required(VERSION 3.20)
project(SPL_Assignment1)

set(CMAKE_CXX_STANDARD 20)

add_executable(SPL_Assignment1 src/main.cpp src/Studio.cpp src/Customer.cpp src/Trainer.cpp src/Workout.cpp src/Action.cpp include/Studio.h include/Customer.h include/Trainer.h include/Workout.h include/Action.h)
