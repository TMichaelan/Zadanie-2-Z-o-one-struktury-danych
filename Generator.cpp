#include <iostream>
#include <cmath>
#include <ctime>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

std::string IntToString(int x);

int main(void)
{
    srand(time(NULL));
    std::string fileName;
    for (int j = 5000; j <= 50000; j += 5000)
    {
        for (int i = 0; i < 10; i++)
        {
            fileName = "Tree" + IntToString(i) + "N" + IntToString(j);
            std::ofstream file(fileName);
            std::cout << fileName << "\n";
            std::vector<int> currentNumber;
            currentNumber.push_back(1);
            for (int k = 1; k < j; k++)
            {
                currentNumber.push_back(currentNumber[currentNumber.size() - 1] + (rand() % 10 + 1));
            }
            std::random_shuffle(currentNumber.begin(), currentNumber.end());
            for (int i = 0; i < currentNumber.size(); i++)
            {
                file << currentNumber[i];
                if (currentNumber.size() - 1 != i)
                    file << "\n";
            }
            file.close();
        }
    }
}

std::string IntToString(int x)
{
    std::stringstream y;
    y << x;
    std::string z;
    y >> z;
    return z;
}
