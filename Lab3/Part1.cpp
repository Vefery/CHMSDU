#include <iostream>
#include <vector>
#include <iomanip>
#define EPS 1e-15

double Func1(double t, double y) {
    return 2 * t * y;
}
double Kn1(double t, double y, double k, double h) {
    return Func1(t + h, y + h*k);
}
int _main() // _ убери
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
    // Р-К
    double prevY = 1, currY = 0, k1, k2, k3, k4;
    for (int i = 0; i < grid.size() - 1; i++)
    {
        k1 = Func1(grid[i], prevY);
        k2 = Kn1(grid[i], prevY, k1, step / 2);
        k3 = Kn1(grid[i], prevY, k2, step / 2);
        k4 = Kn1(grid[i], prevY, k3, step);
        currY = prevY + (step / 6) * (k1 + 2 * k2 + 2 * k3 + k4);
        cout << grid[i + 1] << "\t" << setprecision(15) << currY << endl;
        prevY = currY;
    }
    cout << endl;

    return 0;
}