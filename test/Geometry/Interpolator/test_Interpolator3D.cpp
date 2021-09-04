// ===== TESTS Interpolator 3D =====
int main()
{
   typedef Geom::Interpolator::CubicSplineInterpolator3D CubicSplineInterpolator3D;

   std::size_t size(50);
   Geom::vector3d pos(size), vel(size);
   vector t(size, 0);

   double t0(0);
   double x(0), y(0), z(0);
   double vx(1), vy(1), vz(1);
   for (std::size_t i = 0 ; i < size ; ++i)
   {
       t[i] = t0;
       pos[i].setCoordinates(x, y, z);
       vel[i].setCoordinates(vx, vy, vz);
       t0 += 1;
       x += 1;
       y += 1;
       z += 1;
   }

   for (std::size_t i = 0 ; i < size ; ++i)
   {
       std::cout << "pos[" << t[i] << "] = " << pos[i] << " ; ";
       std::cout << "vel[" << t[i] << "] = " << vel[i] << std::endl;
   }

   auto start = std::chrono::high_resolution_clock::now();
   CubicSplineInterpolator3D fcs(t, pos, vel);
   auto stop = std::chrono::high_resolution_clock::now();
   std::cout << "CubicSplineInterpolator3D initialization time = "
             << duration_cast<std::chrono::microseconds>(stop - start).count()
             << " µs" << std::endl << std::endl;

   vector tinterp;
   for (double tt = 0 ; tt <= t.back() ; tt += 0.000001)
   {
       tinterp.push_back(tt);
   }
   std::size_t tinterpsize(tinterp.size());
   std::cout << "tinterp.size() = " << tinterpsize << std::endl << std::endl;

   start = std::chrono::high_resolution_clock::now();
   std::size_t index = 0;
   Geom::vector3d poscs(tinterpsize), velcs(tinterpsize);
   for (auto it = tinterp.begin() ; it != tinterp.end() ; ++it , ++index)
   {
       // Cubic Spline interpolation of position and velocity
       fcs(*it, poscs[index], velcs[index]);
   }
   stop = std::chrono::high_resolution_clock::now();
   std::cout << "CubicSplineInterpolator3D interpolation time = "
             << duration_cast<std::chrono::milliseconds>(stop - start).count()
             << " ms" << std::endl << std::endl;
}
