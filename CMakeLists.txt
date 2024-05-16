cmake_minimum_required(VERSION 3.22)
set(UNIT_NAME LightWebServer)
project(${UNIT_NAME}Project)



add_subdirectory(Server/src)
add_subdirectory(Client/src)
