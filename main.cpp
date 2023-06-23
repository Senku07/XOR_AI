#include <stdio.h>
#include <math.h>
float data[][3] =
{
    {0,0,1},
    {1,0,1},
    {0,1,1},
    {1,1,0}
} ;

#define data_size (sizeof(data)/sizeof(data[2]))


float sigmoid(float x){
    return 1.0f/(1.0f+expf(-x));
};



float cost(float w1,float w2,float b)
{
    // TODO: y = x1*w1+x2*w2
    float result = 0;    
    for(size_t i = 0; i < data_size;i++)
    {
        float x1 = (data[i][0]);
        float x2 = (data[i][1]);

        float y = sigmoid(x1*w1+x2*w2+b);

        float diff  = y - data[i][2];
        result += diff*diff;
    }
    result = result/data_size;
    return result;
}

int main()
{
    
    float eps = 1e-2;
    float w1 = 1.0f;
    float w2 = 1.0f;
    float b = 1.0f;
    for(size_t i = 0; i <1e6;i++)
    {
        float c = cost(w1,w2,b);
        float dw1 = (cost(w1+eps,w2,b) - c)/eps;
        float dw2 = (cost(w1,w2+eps,b) - c)/eps;
        float db = (cost(w1,w2,b+eps) - c)/eps;
        w1 -= dw1 * 1e-1;
        w2 -= dw2 * 1e-1;
        b -= db * 1e-1;
    }
    
    for (size_t i = 0; i < 2; i++)
    {
        for (size_t j = 0; j < 2; j++)
        {
            printf("%zu | %zu => %f \n",i,j,sigmoid(i*w1+j*w2+b));
        }
        
    }
    
    printf("%f",cost(w1,w2,b));

    return 0;
}