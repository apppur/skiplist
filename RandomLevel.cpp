#include <stdlib.h>
#include "RandomLevel.h"

RandomLevel::RandomLevel(int max, float prob)
{
    m_max = max;
    m_prob = prob;
}

int RandomLevel::Generator()
{
    int level = 1;
    while ((random() % 2 < m_prob) && (level < m_max))
        level++;

    return level;
}
