#include "functions.h"

#include <random>

namespace Utils {

namespace Functions {

int randomNumber(int min, int max)
{
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);
    return dist(rng);
}

}  // namespace Functions

}  // namespace Utils
