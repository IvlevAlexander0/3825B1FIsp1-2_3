#include <iomanip>
#include "tset.h"

using namespace std;

int main()
{
  int n;
  cout << "Тестирование программ поддержки множества" << endl;
  cout << "              Решето Эратосфена" << endl;
  cout << "Введите верхнюю границу целых значений - ";
  if (!(cin >> n) || n < 2)
    return 1;

  TSet s(n + 1);
  for (int m = 2; m <= n; m++)
    s.InsElem(m);
  for (int m = 2; m * m <= n; m++)
    if (s.IsMember(m))
      for (int k = 2 * m; k <= n; k += m)
        s.DelElem(k);

  cout << endl << "Печать множества некратных чисел" << endl << s << endl;
  cout << endl << "Печать простых чисел" << endl;
  int count = 0;
  for (int m = 2; m <= n; m++)
    if (s.IsMember(m))
    {
      count++;
      cout << setw(3) << m << " ";
      if (count % 10 == 0)
        cout << endl;
    }
  cout << endl << "В первых " << n << " числах " << count << " простых" << endl;
  return 0;
}
