g++ -std=c++23 lab4.cpp -o lab4
if [ $? -eq 0 ]; then
    ./lab4
    rm lab4
fi
