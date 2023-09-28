#include <iostream>
#include <vector>
#include <iomanip>
#define EPS 1e-15

double Func(double t, double y) {
    return 2 * t * y;
}

int main()
{
    // Построение сетки
    using namespace std;
    vector<double> grid;
    double step = 0;
    cin >> step;

    grid.push_back(0);

    for (int i = 1; i < 1 / step; i++)
    {
        grid.push_back(step * i);
    }
    grid.push_back(1);
    cout << endl;
    // Метод 1
    double prevY = 1, currY, newY;
    for (int i = 1; i < grid.size(); i++)
    {
        newY = currY = prevY + step * Func(grid[i - 1], prevY);
        do
        {
            currY = newY;
            newY = prevY + step * Func(grid[i], currY);
        } while (fabs(newY - currY) > EPS);
        cout << grid[i] << "\t" << setprecision(15) << newY << endl;
        prevY = currY;
    }
    cout << endl;
    // Метод 2
    prevY = 1;
    for (int i = 1; i < grid.size(); i++)
    {
        newY = currY = prevY + step * Func(grid[i - 1], prevY);
        do
        {
            currY = newY;
            newY = prevY + step * 0.5f * (Func(grid[i-1], prevY) + Func(grid[i], currY));
        } while (fabs(newY - currY) > EPS);
        cout << grid[i] << "\t" << setprecision(15) << newY << endl;
        prevY = currY;
    }
}
