# NauLib
This is a very cool library that totally does things

## Build Instructions

Git clone the library

```
Git clone https://github.com/Lendruk/NauLib
```

### Update submodules with

```
git submodule init

git submodule update
```

### Compile bgfx according to their instructions

It should look something like

```
cd dependencies/bgfx

make

make vs2017-debug64 
```

TODO: bgfx needs to be changed from _ITERATOR_DEBUG_LEVEL=2 to _ITERATOR_DEBUG_LEVEL=0 possible fix: simply compile release instead of debug


### Compile v8

In case of doubts checkout: https://stackoverflow.com/questions/67041878/how-do-i-embed-v8-on-windows 

```
cd dependencies/v8

gclient sync

cd v8

git checkout 9.0.257.19

python tools/dev/v8gen.py x64.debug
```

Change v8\out.gn\x64.debug\args.gn to:

```
is_debug = true
target_cpu = "x64"
v8_enable_backtrace = true
v8_enable_slow_dchecks = true
v8_optimized_debug = false
v8_monolithic = true
v8_use_external_startup_data = false
is_component_build = false
is_clang = false
```

Finally to compile:

```
ninja -C out.gn/x64.debug v8_monolith
```

### Finnally build with 

```
mkdir build

cd build

cmake ..

and 

cmake --build .
```
