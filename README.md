# spline_curve_fitting

This repository contains **Catmull–Rom spline** C++ implementation which fits smooth curve to arbitrary number of points including **angular** or **closed** curves.


## Usage
```
#include <iostream>
#include "spline.hpp"
#include <vector>


int main(){

    std::vector<double> x{10,  0, -10, 0, 10};
    std::vector<double> y{0,  10, 0, -10, 0};
    std::vector<double> x2, y2;

    Spline *sp = new Spline(10);
    sp->setPoints(x, y);
    sp->getSplineCurve(x2, y2);

    for (int i = 0; i < x2.size(); ++i){
        std::cout << x2[i] << "  " << y2[i] << std::endl;
    }

    return 0;
```
