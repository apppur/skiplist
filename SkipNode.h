#ifndef _SKIP_NODE_H
#define _SKIP_NODE_H

struct Node
{
    float   m_score;
    int     m_quantity;
    int     m_location;
};

template <class K, class V> class SkipList;

template <class K, class V> class SkipNode
{
    public:
        SkipNode(K*, V*, int);
        SkipNode(int);
        ~SkipNode();

        K* GetKey();
        V* GetObj();
        int GetLevel();
        SkipNode** m_forwardnodes;

    private:
        int m_level;
        K* m_key;
        V* m_obj;
};

template <class K, class V>
SkipNode<K, V>::~SkipNode()
{
    delete m_key;
    delete m_obj;
    delete [] m_forwardnodes;
}

template <class K, class V>
SkipNode<K, V>::SkipNode(K* key, V* obj, int level)
{
    m_level = level;
    m_key = key;
    m_obj = obj;

    m_forwardnodes = new SkipNode<K, V>* [level + 1];
    for (int i = 1; i <= level; i++)
    {
        m_forwardnodes[i] = nullptr;
    }
}

template <class K, class V>
SkipNode<K, V>::SkipNode(int level)
{
    m_level = level;
    m_key = nullptr;
    m_obj = nullptr;

    m_forwardnodes = new SkipNode<K, V>* [level + 1];
    for (int i = 1; i <= level; i++)
    {
        m_forwardnodes[i] = nullptr;
    }
}

template <class K, class V>
K* SkipNode<K, V>::GetKey()
{
    return m_key;
}

template <class K, class V>
V* SkipNode<K, V>::GetObj()
{
    return m_obj;
}

template <class K, class V>
int SkipNode<K, V>::GetLevel()
{
    return m_level;
}

#endif
