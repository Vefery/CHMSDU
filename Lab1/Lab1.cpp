#include <iostream>
#include <vector>
#include <iomanip>

double Func(double t, double y) {
    return 2 * t * y;
}
int main()
{
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
    // Первый метод
    double prevY = 1;
    double currY = 0;
    for (int i = 0; i <= grid.size(); i++)
    {
        currY = prevY + step * Func(grid[i], prevY);
        cout << grid[i + 1] << "\t" << setprecision(15) << currY << endl;
        prevY = currY;
    }
    cout << endl;
    // Второй метод
    prevY = 1;
    currY = 0;
    for (int i = 1; i < grid.size(); i++)
    {
        currY = prevY + step / 2 * (Func(grid[i-1], prevY) + Func(grid[i], prevY + step * Func(grid[i-1], prevY)));
        cout << grid[i] << "\t" << setprecision(15) << currY << endl;
        prevY = currY;
    }
    cout << endl;
    // Третий метод
    prevY = 1;
    currY = 0;
    for (int i = 1; i < grid.size(); i++)
    {
        currY = prevY + step * Func(grid[i-1] + step/2, prevY + step/2 * Func(grid[i-1], prevY));
        cout << grid[i] << "\t" << setprecision(15) << currY << endl;
        prevY = currY;
    }

    return 0;
}