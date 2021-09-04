// ===== TESTS Vector3D and Rotation3D =====
int main()
{
   Geom::Vector3D vec(1, 0, 0);
   Geom::Vector3D u1(1, 0, 0), v1(0, 1, 0), u2(0, 1, 1), v2(-1, 0, 0);

   Geom::Rotation3D rot(u1, v1, u2, v2);
   Geom::Vector3D rotvec = rot.rotationVector();
   double a1, a2, a3;
   rot.eulerAngles("zyx", a1, a2, a3);

   std::cout << "rot = " << std::endl
             << rot << std::endl << std::endl
             << "rot * vec = " << rot * vec << std::endl << std::endl
             << "rotvec = " << rotvec << std::endl
             << "norm(rotvec) = " << rotvec.norm() << "°" << std::endl
             << "rotvec.normalized() = " << rotvec.normalized() << std::endl << std::endl
             << "Euler angles : a1 = " << a1 << "° ; a2 = " << a2 << "° ; a3 = " << a3 << "°" << std::endl;

   return 0;
}

====== TESTS ROOTS ======
int main()
{
   double a(3), b(6), c(-123), d(-126), e(1080);
   complex x1, x2, x3, x4;
   Maths::Roots::quarticRoots(a, b, c, d, e, x1, x2, x3, x4);

   std::cout << std::scientific;
   std::cout << "x1 = " << x1 << std::endl
             << "x2 = " << x2 << std::endl
             << "x3 = " << x3 << std::endl
             << "x4 = " << x4 << std::endl << std::endl;

   return 0;
}
