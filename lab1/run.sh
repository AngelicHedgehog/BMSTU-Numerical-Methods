g++ -std=c++23 lab1.cpp -o lab1
if [ $? -eq 0 ]; then
    ./lab1
    rm lab1
fi
