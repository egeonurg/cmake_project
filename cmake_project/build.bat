mkdir build
cd build && cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -D "CMAKE_TOOLCHAIN_FILE=../cmake/xmc4500.cmake" ../