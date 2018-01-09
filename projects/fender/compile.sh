cd build
make
cp libfender.a ../demo
cp libfender.a ../release
cd ../demo/build

make
cd ..
./demo
cd ..
