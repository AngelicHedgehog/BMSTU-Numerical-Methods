g++ -std=c++23 lab2.cpp -o lab2
if [ $? -eq 0 ]; then
    ./lab2
    rm lab2
fi
