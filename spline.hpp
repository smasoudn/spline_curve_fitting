#include <assert.h>
#include <vector>

// 2D Point
////////////////////////////////////////////
struct Point2D{
    double x;
    double y;
    Point2D(double a, double b) : x(a), y(b){}
    Point2D (){}
};


// 1D Catmull-Rom Spline
////////////////////////////////////////////
class CatmullRomSpline1D{

private:
    double p0, p1, p2, p3;

public:
    CatmullRomSpline1D(double p0, double p1, double p2, double p3){
        this->p0 = p0;
        this->p1 = p1;
        this->p2 = p2;
        this->p3 = p3;
    }

    double q(double t) {
        return 0.5f * ((2 * p1) +
                       (p2 - p0) * t +
                       (2*p0 - 5*p1 + 4*p2 - p3) * t * t +
                       (3*p1 -p0 - 3 * p2 + p3) * t * t * t);
    }
};


//  Main spline class
////////////////////////////////////////////
class Spline{

private:
    std::vector<Point2D> pts_;
    std::vector<Point2D> result_;
    int num_pts_;

public:

    // Constructor
    ///////////////////////
    Spline(int x){
        this->num_pts_ = x;                            // number of interpolated points between every two points
    }

    // Deconstructor
    ///////////////////////
    ~Spline(){}


    // Set points
    ///////////////////////
    void setPoints(std::vector<double> x, std::vector<double> y){

        assert(x.size() == y.size());       // x and y must be the same size
        assert(x.size() >= 4);                   // at least four points needed

        result_.resize((x.size()-1) * num_pts_ + 1);
        double inc = 1.0 / (double)num_pts_;

        for (unsigned int i = 0; i < x.size(); ++i){
            Point2D pt = Point2D(x[i], y[i]);
            pts_.push_back(pt);
        }



        for (unsigned int i = 0; i < pts_.size()-1; i++) {
           Point2D p0 = i == 0 ? pts_[i] : pts_[i-1];
           Point2D p1 = pts_[i];
           Point2D p2 = pts_[i+1];
           Point2D p3 = (i+2 == pts_.size()) ? pts_[i+1] : pts_[i+2];

           CatmullRomSpline1D spline_x = CatmullRomSpline1D(p0.x, p1.x, p2.x, p3.x);
           CatmullRomSpline1D spline_y = CatmullRomSpline1D(p0.y, p1.y, p2.y, p3.y);

           for (int j = 0; j <= num_pts_; ++j){
                double r_x = spline_x.q((double)j * inc);
                double r_y = spline_y.q((double)j * inc);

                Point2D tmp = Point2D(r_x, r_y);

                result_[(i * num_pts_) + j] =  tmp;
           }

        }
    }

    // Get fitted curve
    ///////////////////////
    void getSplineCurve(std::vector<double>& x, std::vector<double>& y){
        for (unsigned int i = 0; i < result_.size(); ++i){
            x.push_back(result_[i].x);
            y.push_back(result_[i].y);
        }
    }

};
