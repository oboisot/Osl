// ====== TESTS ROOTS ======
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
