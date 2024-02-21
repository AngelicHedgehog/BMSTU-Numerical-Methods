g++ -std=c++23 lab1.1.cpp -o lab1.1
if [ $? -eq 0 ]; then
    ./lab1.1
    rm lab1.1
fi
