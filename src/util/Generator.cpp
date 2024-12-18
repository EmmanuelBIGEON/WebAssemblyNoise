#include "Generator.h"

#include <random>

std::vector<glm::vec2> Generator::GeneratePoints(unsigned int nbPoints, float xmin, float xmax, float ymin, float ymax)
{
    std::vector<glm::vec2> points;
    std::default_random_engine generator;
    std::uniform_real_distribution<float> distributionX(xmin, xmax);
    std::uniform_real_distribution<float> distributionY(ymin, ymax);

    for (int i = 0; i < nbPoints; ++i) {
        points.emplace_back(distributionX(generator), distributionY(generator));
    }

    return points;
}