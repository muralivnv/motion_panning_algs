#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <cstdlib>

struct Pose{
    double x = 0.0, y = 0.0, theta = 0.0;
};

struct CircleConfig{
    double xc = 0.0, yc = 0.0, rad = 0.0, final_angle = 0.0;
};

void create_path(double x_target, std::vector<Pose>& ref_path)
{
    const int num_of_circles = 2;

    std::array<CircleConfig, num_of_circles> circles;
    std::array<double, num_of_circles> final_time{{25.0,25.0}};
    
    circles[0].xc = x_target;
    circles[0].rad = x_target;
    circles[0].final_angle = M_PI;

    circles[1].xc = x_target + x_target*0.5;
    circles[1].rad = x_target*0.5;
    circles[1].final_angle = 2*M_PI;
    
    Pose current_pose;
    double start_angle = 0.0, start_x = 0.0, start_y= 0.0;

    for (int idx = 0; idx < num_of_circles; ++idx)
    {
        double X_center = circles[idx].xc;
        double Y_center = circles[idx].yc;
        double radius = circles[idx].rad;
        double t_final = final_time[idx];

        for (double t = 0.0; t <= t_final; t += 1.0)
        {
            current_pose.x = X_center + start_x + radius * std::cos(circles[idx].final_angle*t/t_final + start_angle);
            current_pose.y = Y_center + start_y + radius * std::sin(circles[idx].final_angle*t/t_final + start_angle);
            current_pose.theta = circles[idx].final_angle*t/t_final + start_angle;

        //    if (idx > 0);
              { ref_path.push_back(current_pose); }
        }
        break;
        start_angle = circles[idx].final_angle;
        start_x = current_pose.x;
        start_y = current_pose.y;
    }
    ref_path.erase(std::end(ref_path)-1, std::end(ref_path));

}

int main()
{
    std::vector<Pose> ref_path;

    create_path(10.0, ref_path);


    /* plotting */

    std::ofstream path_data, plot;
    
    path_data.open("create_spiral_traj_data.dat", std::ofstream::out);
    
    path_data << "#X" << std::setw(14) << " " << "#Y\n";
    for (Pose& elem : ref_path)
    {
        path_data << elem.x << std::setw(8) << " " << elem.y << '\n';
    }
    path_data.close();


    plot.open("create_spiral_traj_plot.plt", std::ofstream::out);
    
    plot << "set term qt 0 position 100,100\n";
    plot << "plot 'create_spiral_traj_data.dat' u 1:2 w l t 'reference'\n";
    plot << "set grid\n";
    plot << "set xlabel 'X(m)' \n";
    plot << "set ylabel 'Y(m)' \nreplot\n";

    plot.close();

    std::system("gnuplot -p create_spiral_traj_plot.plt");


    return EXIT_SUCCESS;
}
