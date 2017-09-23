# build the project in current dir and gen Makefiles and store them in build folder 
cmake . -Bbuild

# now invoke command "make" in "build" to generate binaries
cmake --build build
