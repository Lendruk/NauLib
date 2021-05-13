cd dependencies/bgfx
make
make vs2017-debug64
cd ..
cd ..
mkdir ../build
cd NauLib
cmake -S . -B ../build
cd ../build
cmake --build .