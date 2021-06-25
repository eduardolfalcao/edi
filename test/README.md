# Instrucoes para GTEST no Ubuntu

Fonte: https://www.eriksmistad.no/getting-started-with-google-test-on-ubuntu/

```bash
sudo apt-get install libgtest-dev cmake

cd /usr/src/gtest
sudo cmake CMakeLists.txt
sudo make

# copy or symlink libgtest.a and libgtest_main.a to your /usr/lib folder
# necessario apenas em versoes mais antigas
sudo cp *.a /usr/lib

cmake CMakeLists.txt
make
./runTests
```


