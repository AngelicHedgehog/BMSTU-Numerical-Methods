g++ -std=c++23 lab5.1.cpp -o lab5
if [ $? -eq 0 ]; then
    ./lab5
    rm lab5
fi
