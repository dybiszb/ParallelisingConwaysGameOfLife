project(conway C CXX)

set(CMAKE_CXX_STANDARD 11)

include_directories(conway_lib)
SET(LIB_SOURCE_FILES
        conway_lib/conway.cpp
        conway_lib/game_grid.cpp
        conway_lib/strategies.cpp
        conway_lib/utilities.cpp
        conway_lib/io.cpp)

add_library(Conway ${LIB_SOURCE_FILES})

add_executable(ConwayApp conway_app/main.cpp)
TARGET_LINK_LIBRARIES(ConwayApp Conway)