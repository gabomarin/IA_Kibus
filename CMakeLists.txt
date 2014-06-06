project(sdl_engine)

add_executable(sdl_engine ../src/mapa.cpp ../src/slider.cpp  ../src/button.cpp  ../src/bee.cpp ../src/kimbus.cpp  src/hero.cpp main.cpp src/timer.cpp)

install(TARGETS sdl_engine RUNTIME DESTINATION bin)

set(CMAKE_EXE_LINKER_FLAGS "-lSDL -lGL -lSDL_image  -lSDL_ttf -zmuldefs")

add_subdirectory(src)
add_subdirectory(include)
add_subdirectory(resources)