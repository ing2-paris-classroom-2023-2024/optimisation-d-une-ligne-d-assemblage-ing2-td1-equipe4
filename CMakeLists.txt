cmake_minimum_required(VERSION 3.26)
project(optimisation_d_une_ligne_d_assemblage_ing2_td1_equipe4 C)

set(CMAKE_C_STANDARD 99)
include_directories(.)

add_executable(optimisation_d_une_ligne_d_assemblage_ing2_td1_equipe4 main.c main.h tests.h tests.c exclusion.c exclusion.h)
