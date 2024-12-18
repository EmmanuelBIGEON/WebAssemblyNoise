#pragma once 

#include <vector>
#include <glm/ext.hpp>

class Generator
{
    public:
        static std::vector<glm::vec2> GeneratePoints(unsigned int nbPoints, float xmin, float xmax, float ymin, float ymax);
        
};