
file(GLOB_RECURSE source
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
)


add_executable(${UNIT_NAME}Target ${source})

