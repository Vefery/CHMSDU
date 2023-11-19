#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;
vector<double> grid;
double step = 0;

int Sign(double value) {
    if (value >= 0)
        return 1;
    else
        return -1;
}

void BuildGrid()
{
    grid.push_back(0);
    for (int i = 1; i < 20 / step; i++)
    {
        grid.push_back(step * i);
    }
    grid.push_back(20);
}

double Qn(double t) {
    if (t > 1)
        return 1e-3;
    else
        return 1e-3 * t;
}

double P1(double t, double q2) {
    double s = (M_PI * 1e-2 * 1e-2) / 4;
    double c = s / (1000 * 1260 * 1260);
    return (Qn(t) - q2) / c;
}

double Q2(double t, double p1, double q2) {
    double s = (M_PI * 1e-2 * 1e-2) / 4;
    double pDiff = abs(p1 - 1e+5);
    double ksi = 1 - cos(M_PI_4);
    return sqrt((ksi * pDiff / (2 * 1000))) * (s * sqrt(((2 * pDiff) / (1000 * ksi))) * Sign(pDiff) - q2);
}

double PKn(double t, double q2, double k, double h) {
    return P1(t + h, q2 + h * k);
}

double QKn(double t, double q2, double kq, double p1, double kp, double h) {
    return Q2(t + h, p1 + h * kp, q2 + h * kq);
}

void DirectMethod() {
    double pk1, pk2, pk3, pk4, currP1;
    double qk1, qk2, qk3, qk4, currQ2;
    double prevQ2 = 0;
    double prevP1 = 1e+5;
    int i;

    cout /*<< "t" << "\t"*/ << setprecision(15)/* << "P1" << "\t\t"*/ << "Q2" << endl;
    cout /*<< grid[0] << "\t"*/ << setprecision(15) /*<< prevP1 << "\t\t"*/ << prevQ2 << endl;
    for (i = 0; i < grid.size() - 1; i++)
    {
        pk1 = P1(grid[i], prevQ2);
        qk1 = Q2(grid[i], prevP1, prevQ2);

        pk2 = PKn(grid[i], prevQ2, qk1, step / 2);
        qk2 = QKn(grid[i], prevQ2, qk1, prevP1, pk1, step / 2);

        pk3 = PKn(grid[i], prevQ2, qk2, step / 2);
        qk3 = QKn(grid[i], prevQ2, qk2, prevP1, pk2, step / 2);

        pk4 = PKn(grid[i], prevQ2, qk3, step);
        qk4 = QKn(grid[i], prevQ2, qk3, prevP1, pk3, step);

        currP1 = prevP1 + (step / 6) * (pk1 + 2 * pk2 + 2 * pk3 + pk4);
        currQ2 = prevQ2 + (step / 6) * (qk1 + 2 * qk2 + 2 * qk3 + qk4);

        if (grid[i + 1] == 10 || i == grid.size() - 2)
            cout << grid[i + 1] << "\t\t" << setprecision(15) << currP1 << "\t\t" << currQ2 << endl;
        prevP1 = currP1;
        prevQ2 = currQ2;
    }
}

void SequentialMethod() {
    double pk1, pk2, pk3, pk4, currP1;
    double qk1, qk2, qk3, qk4, currQ2;
    double prevQ2 = 0;
    double prevP1 = 1e+5;
    int i;

    //cout /*<< "t" << "\t"*/ << setprecision(15) /*<< "P1" << "\t\t"*/ << "Q2" << endl;
    cout /*<< grid[0] << "\t"*/ << setprecision(15) /*<< prevP1 << "\t\t"*/ << prevQ2 << endl;
    for (i = 0; i < grid.size() - 1; i++)
    {
        pk1 = P1(grid[i], prevQ2);
        pk2 = PKn(grid[i], prevQ2, 0, step / 2);
        pk3 = PKn(grid[i], prevQ2, 0, step / 2);
        pk4 = PKn(grid[i], prevQ2, 0, step);

        currP1 = prevP1 + (step / 6) * (pk1 + 2 * pk2 + 2 * pk3 + pk4);
        prevP1 = currP1;

        qk1 = Q2(grid[i], prevP1, prevQ2);
        qk2 = QKn(grid[i], prevQ2, qk1, prevP1, 0, step / 2);
        qk3 = QKn(grid[i], prevQ2, qk2, prevP1, 0, step / 2);
        qk4 = QKn(grid[i], prevQ2, qk3, prevP1, 0, step);

        currQ2 = prevQ2 + (step / 6) * (qk1 + 2 * qk2 + 2 * qk3 + qk4);
        prevQ2 = currQ2;

        if (grid[i + 1] == 10 || i == grid.size() - 2)
            cout << grid[i + 1] << "\t\t" << setprecision(15) << currP1 << "\t\t" << currQ2 << endl;
    }
}

int main()
{
    cin >> step;
    BuildGrid();
    cout << endl;
    //DirectMethod();
    SequentialMethod();
    return 0;
}
