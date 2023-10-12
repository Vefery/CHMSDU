#include <iostream>
#include <vector>
#include <iomanip>
#define EPS 1e-15

double Func2(double t, double x) {
    return -25 * x + cos(t) + 25 * sin(t);
}
double Kn2(double t, double y, double k, double h) {
    return Func2(t + h, y + h * k);
}
int main()
{
    using namespace std;
    vector<double> grid;
    double step = 0;
    cin >> step;

    grid.push_back(0);

    for (int i = 1; i < 2 / step; i++)
    {
        grid.push_back(step * i);
    }
    grid.push_back(2);
    cout << endl;
    // Эйлер простой неявный
    double prevY = 1, prevX, currX = 0, derivative;
    derivative = -25 * step - 1;
    for (int i = 1; i < grid.size(); i++)
    {
        prevX = -1;
        while (fabs(prevX - currX) > EPS)
        {
            prevX = currX;
            currX = prevX - (prevY + step * Func2(grid[i], prevX) - prevX) / derivative;
        }
        cout << grid[i] << "\t" << setprecision(15) << currX << endl;
        prevY = currX;
    }
    cout << endl;
    // Простой Эйлер (да, его хуярит знатно, но я проверил на первой функции и работает)
    prevY = 1;
    double currY = 0;
    for (int i = 0; i < grid.size() - 1; i++)
    {
        currY = prevY + step * Func2(grid[i], prevY);
        cout << grid[i + 1] << "\t" << setprecision(15) << currY << endl;
        prevY = currY;
    }
    cout << endl;
    // Модифицированный Эйлер (его тоже колбасит)
    prevY = 1;
    currY = 0;
    for (int i = 1; i < grid.size(); i++)
    {
        currY = prevY + step / 2 * (Func2(grid[i - 1], prevY) + Func2(grid[i], prevY + step * Func2(grid[i - 1], prevY)));
        cout << grid[i] << "\t" << setprecision(15) << currY << endl;
        prevY = currY;
    }
    cout << endl;
    // Трапеция
    double prevY = 1, prevX, currX = 0, derivative;
    derivative = -25 * step / 2 - 1;
    for (int i = 1; i < grid.size(); i++)
    {
        prevX = -1;
        while (fabs(prevX - currX) > EPS)
        {
            prevX = currX;
            currX = prevX - (prevY + step * (Func2(grid[i - 1], prevY) + Func2(grid[i], prevX)) - prevX) / derivative;
        }
        cout << grid[i] << "\t" << setprecision(15) << currX << endl;
        prevY = currX;
    }
    cout << endl;
    // Р-К
    double k1, k2, k3, k4;
    prevY = 1, currY = 0;
    for (int i = 0; i < grid.size() - 1; i++)
    {
        k1 = Func2(grid[i], prevY);
        k2 = Kn2(grid[i], prevY, k1, step / 2);
        k3 = Kn2(grid[i], prevY, k2, step / 2);
        k4 = Kn2(grid[i], prevY, k3, step);
        currY = prevY + (step / 6) * (k1 + 2 * k2 + 2 * k3 + k4);
        cout << grid[i + 1] << "\t" << setprecision(15) << currY << endl;
        prevY = currY;
    }
    cout << endl;
    return 0;
}