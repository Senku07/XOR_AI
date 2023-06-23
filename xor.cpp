#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
    double or_w1;
    double or_w2;
    double or_b;
    double and_w1;
    double and_w2;
    double and_b;
    double nand_w1;
    double nand_w2;
    double nand_b;
} xor ;

double sigmoid(double x)
{
    return 1. / (1.0 + expf(-x));
}

double forward(xor m, double x, double y)
{
    double a = sigmoid(m.or_w1 * x + m.or_w2 * y + m.or_b);
    double b = sigmoid(m.nand_w1 * x + m.nand_w2 * y + m.nand_b);
    return sigmoid(m.and_w1 * a + m.and_w2 * b + m.and_b);
}

double data[][3] = {
    {0, 0, 1},
    {1, 0, 1},
    {0, 1, 1},
    {1, 1, 0}};

#define size_data (sizeof(data) / sizeof(data[1]))

double cost(xor m)
{
    double r = 0;
    for (int i = 0; i < size_data; i++)
    {
        double x1 = data[i][0];
        double x2 = data[i][1];

        double y = forward(m, x1, x2);
        double d = y - data[i][2];
        r += d * d;
    }
    r = r / 4.0;
    return r;
}

xor random_xor() {
  xor m;
  srand(time(0));
  m.or_w1 = (double)rand() / (double)RAND_MAX;
  m.or_w2 = (double)rand() / (double)RAND_MAX;
  m.or_b = (double)rand() / (double)RAND_MAX;
  m.and_w1 = (double)rand() / (double)RAND_MAX;
  m.and_w2 = (double)rand() / (double)RAND_MAX;
  m.and_b = (double)rand() / (double)RAND_MAX;
  m.nand_w1 = (double)rand() / (double)RAND_MAX;
  m.nand_w2 = (double)rand() / (double)RAND_MAX;
  m.nand_b = (double)rand() / (double)RAND_MAX;

  return m;
}

int main()
{
    xor v = random_xor();
    printf("Cost : %lf \n", cost(v));
    double eps = 1e-3;
    double rate = 1e-1;

    for (size_t i = 0; i < 1e6; i++)
    {
        double c = cost(v);
        // printf("Cost : %f \n", c);
        xor temp = v;

        temp.or_w1 += eps;
        double or_d1 = (cost(temp) - c) / eps;
        v.or_w1 -= or_d1 * rate;

        temp.or_w2 += eps;
        double or_d2 = (cost(temp) - c) / eps;
        v.or_w2 -= or_d2 * rate;

        temp.or_b += eps;
        double or_d3 = (cost(temp) - c) / eps;
        v.or_b -= or_d3 * rate;

        temp.nand_w1 += eps;
        double nand_d1 = (cost(temp) - c) / eps;
        v.nand_w1 -= nand_d1 * rate;

        temp.nand_w2 += eps;
        double nand_d2 = (cost(temp) - c) / eps;
        v.nand_w2 -= nand_d2 * rate;

        temp.nand_b += eps;
        double nand_d3 = (cost(temp) - c) / eps;
        v.nand_b -= nand_d3 * rate;

        temp.and_w1 += eps;
        double and_d1 = (cost(temp) - c) / eps;
        v.and_w1 -= and_d1 * rate;

        temp.and_w2 += eps;
        double and_d2 = (cost(temp) - c) / eps;
        v.and_w2 -= and_d2 * rate;

        temp.and_b += eps;
        double and_d3 = (cost(temp) - c) / eps;
        v.and_b -= and_d3 * rate;
    }

    printf("%lf", cost(v));

    printf("\n-------------------------------\n");

    for (size_t i = 0; i < 2; i++)
    {
        for (size_t j = 0; j < 2; j++)
        {
            printf("%zu ^ %zu = %lf \n",i,j,forward(v,i,j));
        }
    }


    printf("\n------------OR-------------------\n");
     for (size_t i = 0; i < 2; i++)
    {
        for (size_t j = 0; j < 2; j++)
        {
            printf("%zu ^ %zu = %lf \n",i,j,sigmoid(v.or_w1 * i + v.or_w2 * j + v.or_b));
        }
    }

    return 0;
}
