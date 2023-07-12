cmake_minimum_required(VERSION 3.12)

project(homework_2)

add_executable(homework_2
	main.cpp
)

set_target_properties(
    homework_2 PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
)
