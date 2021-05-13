# NauLib
This is a very cool library that totally does things

# Build Instructions

git clone the library

git clone https://github.com/Lendruk/NauLib



Update submodules with

git submodule init
git submodule update



Compile bgfx according to their instructions

It should look something like

cd dependencies/bgfx

make

make vs2017-debug64



Finnally build with 

cmake .

and 

cmake --build .