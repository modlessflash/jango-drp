cmake_minimum_required(VERSION 3.11)
project("jango-drp")

set(LIBS discord-rpc)

add_subdirectory("discord-rpc")

add_executable(jango-drp main.cpp)
foreach(LIB ${LIBS})
	target_link_libraries(jango-drp ${LIB})
endforeach()






