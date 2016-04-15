#ifndef _RANDOM_LEVEL_H
#define _RANDOM_LEVEL_H

class RandomLevel
{
    public:
        RandomLevel(int max, float prob);
        ~RandomLevel() {}

        int Generator();
    private:
        int m_max;
        float m_prob;
};
#endif
