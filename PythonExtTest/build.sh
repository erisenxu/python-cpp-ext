g++ -c -Wall -fPIC -D_GNU_SOURCE  -I./Python/Python-2.7.13 -I./Python/Python-2.7.13/Include BasePy.cpp
g++ -c -Wall -fPIC -D_GNU_SOURCE  -I./Python/Python-2.7.13 -I./Python/Python-2.7.13/Include SubClassPy.cpp
g++ -c -Wall -fPIC -D_GNU_SOURCE  -I./Python/Python-2.7.13 -I./Python/Python-2.7.13/Include OtherPy.cpp
g++ -c -Wall -fPIC -D_GNU_SOURCE  -I./Python/Python-2.7.13 -I./Python/Python-2.7.13/Include Main.cpp

g++ -o tests.so -shared -fPIC BasePy.o SubClassPy.o OtherPy.o Main.o

