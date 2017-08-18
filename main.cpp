#include <iostream>
#include "spline.hpp"
#include <vector>


using namespace std;

int main(){

    vector<double> x{10,  0, -10, 0, 10};
    vector<double> y{0,  10, 0, -10, 0};
    vector<double> x2, y2;

    Spline *sp = new Spline(10);
    sp->setPoints(x, y);
    sp->getSplineCurve(x2, y2);

    for (int i = 0; i < x2.size(); ++i){
        cout << x2[i] << "  " << y2[i] << endl;
    }

    return 0;
}
