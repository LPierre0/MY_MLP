#include "Function.hpp"


float relu(float x){
    return (x > 0 ? x : 0);
}


float relu_derivate(float x){
    return (x > 0 ? 1 : 0);
}


