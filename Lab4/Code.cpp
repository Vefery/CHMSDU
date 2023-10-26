#include <iostream>
#include <vector>
#include <iomanip>
#define EPS 1e-15

using namespace std;
vector<double> grid;
double step = 0;

double Func(double t, double y) {
    return 2*t*y;
}

void BuildGrid()
{
    grid.push_back(0);
    for (int i = 1; i < 1 / step; i++)
    {
        grid.push_back(step * i);
    }
    grid.push_back(1);
}

double Kn(double t, double y, double k, double h) {
    return Func(t + h, y + h * k);
}

double RK(double t, double prevY) 
{
    double k1, k2, k3, k4;
    k1 = Func(t, prevY);
    k2 = Kn(t, prevY, k1, step / 2);
    k3 = Kn(t, prevY, k2, step / 2);
    k4 = Kn(t, prevY, k3, step);
    return prevY + (step / 6) * (k1 + 2 * k2 + 2 * k3 + k4);
}

void AdamsBashforth3() {
    double fn[3];
    double prevY = 1;
    double currY = 0;
    fn[0] = 1;
    for (int i = 1; i < 3; i++)
    {
        cout << grid[i - 1] << "\t" << setprecision(15) << fn[i - 1] << endl;
        fn[i] = RK(grid[i - 1], fn[i - 1]);
        fn[i - 1] = Func(grid[i - 1], fn[i - 1]);
    }
    cout << grid[2] << "\t" << setprecision(15) << fn[2] << endl;
    prevY = fn[2];
    fn[2] = Func(grid[2], prevY);
    for (int i = 3; i < grid.size(); i++)
    {
        currY = prevY + (step / 12) * (23 * fn[2] - 16 * fn[1] + 5 * fn[0]);
        cout << grid[i] << "\t" << setprecision(15) << currY << endl;
        prevY = currY;
        fn[0] = fn[1];
        fn[1] = fn[2];
        fn[2] = Func(grid[i], prevY);
    }
}

void AdamsBashforth4() {
    double fn[4];
    double prevY = 1;
    double currY = 0;
    fn[0] = 1;
    for (int i = 1; i < 4; i++)
    {
        cout << grid[i - 1] << "\t" << setprecision(15) << fn[i - 1] << endl;
        fn[i] = RK(grid[i - 1], fn[i - 1]);
        fn[i - 1] = Func(grid[i - 1], fn[i - 1]);
    }
    cout << grid[3] << "\t" << setprecision(15) << fn[3] << endl;
    prevY = fn[3];
    fn[3] = Func(grid[3], prevY);
    for (int i = 4; i < grid.size(); i++)
    {
        currY = prevY + (step / 24) * (55 * fn[3] - 59 * fn[2] + 37 * fn[1] - 9 * fn[0]);
        cout << grid[i] << "\t" << setprecision(15) << currY << endl;
        prevY = currY;
        fn[0] = fn[1];
        fn[1] = fn[2];
        fn[2] = fn[3];
        fn[3] = Func(grid[i], prevY);
    }
}

void AdamsMoulton3() {
    double prevY = 1, currY, newY;
    double fn[2];

    fn[0] = 1;
    for (int i = 1; i < 2; i++)
    {
        cout << grid[i - 1] << "\t" << setprecision(15) << fn[i - 1] << endl;
        fn[i] = RK(grid[i - 1], fn[i - 1]);
        fn[i - 1] = Func(grid[i - 1], fn[i - 1]);
    }
    cout << grid[1] << "\t" << setprecision(15) << fn[1] << endl;
    prevY = fn[1];
    fn[1] = Func(grid[1], prevY);

    for (int i = 2; i < grid.size(); i++)
    {
        newY = currY = RK(grid[i-1], prevY);
        do
        {
            currY = newY;
            newY = prevY + (step / 12) * (5 * Func(grid[i], currY) + 8 * fn[1] - fn[0]);
        } while (fabs(newY - currY) > EPS);
        cout << grid[i] << "\t" << setprecision(15) << newY << endl;
        prevY = currY;
        fn[0] = fn[1];
        fn[1] = Func(grid[i], currY);
    }
}

void AdamsMoulton4() {
    double prevY = 1, currY, newY;
    double fn[3];

    fn[0] = 1;
    for (int i = 1; i < 3; i++)
    {
        cout << grid[i - 1] << "\t" << setprecision(15) << fn[i - 1] << endl;
        fn[i] = RK(grid[i - 1], fn[i - 1]);
        fn[i - 1] = Func(grid[i - 1], fn[i - 1]);
    }
    cout << grid[2] << "\t" << setprecision(15) << fn[2] << endl;
    prevY = fn[2];
    fn[2] = Func(grid[2], prevY);

    for (int i = 3; i < grid.size(); i++)
    {
        newY = currY = RK(grid[i - 1], prevY);
        do
        {
            currY = newY;
            newY = prevY + (step / 24) * (9 * Func(grid[i], currY) + 19 * fn[2] - 5 * fn[1] + fn[0]);
        } while (fabs(newY - currY) > EPS);
        cout << grid[i] << "\t" << setprecision(15) << newY << endl;
        prevY = currY;
        fn[0] = fn[1];
        fn[1] = fn[2];
        fn[2] = Func(grid[i], currY);
    }
}

void PredictorCorrector3() {
    double fn[3];
    double prevY = 1;
    double currY = 0;
    double predict;
    fn[0] = 1;
    for (int i = 1; i < 3; i++)
    {
        cout << grid[i - 1] << "\t" << setprecision(15) << fn[i - 1] << endl;
        fn[i] = RK(grid[i - 1], fn[i - 1]);
        fn[i - 1] = Func(grid[i - 1], fn[i - 1]);
    }
    cout << grid[2] << "\t" << setprecision(15) << fn[2] << endl;
    prevY = fn[2];
    fn[2] = Func(grid[2], prevY);

    for (int i = 3; i < grid.size(); i++)
    {
        predict = prevY + (step / 12) * (23 * fn[2] - 16 * fn[1] + 5 * fn[0]);
        currY = prevY + (step / 12) * (5 * Func(grid[i], predict) + 8 * fn[2] - fn[1]);

        cout << grid[i] << "\t" << setprecision(15) << currY << endl;
        prevY = currY;
        fn[0] = fn[1];
        fn[1] = fn[2];
        fn[2] = Func(grid[i], currY);
    }
}

void PredictorCorrector4() {
    double fn[4];
    double prevY = 1;
    double currY = 0;
    double predict;
    fn[0] = 1;
    for (int i = 1; i < 4; i++)
    {
        cout << grid[i - 1] << "\t" << setprecision(15) << fn[i - 1] << endl;
        fn[i] = RK(grid[i - 1], fn[i - 1]);
        fn[i - 1] = Func(grid[i - 1], fn[i - 1]);
    }
    cout << grid[3] << "\t" << setprecision(15) << fn[3] << endl;
    prevY = fn[3];
    fn[3] = Func(grid[3], prevY);

    for (int i = 4; i < grid.size(); i++)
    {
        predict = prevY + (step / 24) * (55 * fn[3] - 59 * fn[2] + 37 * fn[1] - 9 * fn[0]);
        currY = prevY + (step / 24) * (9 * Func(grid[i], predict) + 19 * fn[3] - 5 * fn[2] + fn[1]);

        cout << grid[i] << "\t" << setprecision(15) << currY << endl;
        prevY = currY;
        fn[0] = fn[1];
        fn[1] = fn[2];
        fn[2] = fn[3];
        fn[3] = Func(grid[i], prevY);
    }
}

int main()
{
    cin >> step;
    BuildGrid();
    cout << endl;
    PredictorCorrector4();
    return 0;
}