#ifndef _SKIP_LIST_H
#define _SKIP_LIST_H

#include <iostream>
#include <fstream>
#include "SkipNode.h"
#include "RandomLevel.h"

using namespace std;

template <class K, class V>
class SkipList
{
    public:
        SkipList(float prob, int max, K* key);
        ~SkipList();

        bool Insert(K* key, V* obj);
        bool Remove(K* key);
        V* Retrieve(K* key);
        void Dump(ofstream& of);
        void Dump();

    private:
        SkipNode<K, V>* head;
        SkipNode<K, V>* tail;
        float m_prob;
        int m_maxlevel;
        int m_curlevel;
        RandomLevel* m_random;
};

template <class K, class V>
SkipList<K, V>::SkipList(float prob, int max, K* key)
{
    m_curlevel = 1;
    m_maxlevel = max;
    m_prob = prob;
    m_random = new RandomLevel(max, prob);

    head = new SkipNode<K, V>(m_maxlevel);
    tail = new SkipNode<K, V>(key, nullptr, m_maxlevel);
    for (int i = 1; i <= m_maxlevel; i++)
    {
        head->m_forwardnodes[i] = tail;
    }
}

template <class K, class V>
SkipList<K, V>::~SkipList()
{
    SkipNode<K, V>* curr;
    SkipNode<K, V>* next;
    curr = head;
    while (curr)
    {
        next = curr->m_forwardnodes[1];
        delete curr;
        curr = next;
    }
}

template <class K, class V>
bool SkipList<K, V>::Insert(K* key, V* obj)
{
    int level = 0; 
    int h = 0;
    SkipNode<K, V>** update = new SkipNode<K, V>* [m_maxlevel+1];
    SkipNode<K, V>* curr = head;
    K* cmp;

    for (h = m_curlevel; h >= 1; h--)
    {
        cmp = curr->m_forwardnodes[h]->GetKey();
        while (*cmp < *key)
        {
            curr = curr->m_forwardnodes[h];
            cmp = curr->m_forwardnodes[h]->GetKey();
        }
        update[h] = curr;
    }

    curr = curr->m_forwardnodes[1];
    cmp = curr->GetKey();
    if (*cmp == *key)
    {
        return false;
    } 
    else
    {
        level = m_random->Generator();
        if (level > m_curlevel)
        {
            for (int i = m_curlevel+1; i <= level; i++)
            {
                update[i] = head;
            }
            m_curlevel = level;
        }
        SkipNode<K, V>* node = new SkipNode<K, V>(key, obj, level);
        for (int i = 1; i <= level; i++)
        {
            node->m_forwardnodes[i] = update[i]->m_forwardnodes[i];
            update[i]->m_forwardnodes[i] = node;
        }
    }

    return true;
}

template <class K, class V>
bool SkipList<K, V>::Remove(K* key)
{
    SkipNode<K, V>** update = new SkipNode<K, V>* [m_maxlevel];
    SkipNode<K, V>* curr = head;
    K* cmp;

    for (int h = m_curlevel; h > 0; h--)
    {
        cmp = curr->m_forwardnodes[h]->GetKey();
        while (*cmp < *key)
        {
            curr = curr->m_forwardnodes[h];
            cmp = curr->forward[h]->GetKey();
        }
        update[h] = curr;
    }
    curr = curr->m_forwardnodes[1];
    cmp = curr->GetKey();

    if (*cmp == *key)
    {
        for (int i = 1; i <= m_curlevel; i++)
        {
            if (update[i]->m_forwardnodes[i] != curr)
                break;
            update[i]->m_forwardnodes[i] = curr->m_forwardnodes[i];
        }
        delete curr;
        while ((m_curlevel > 1) && ((head->forwardnode[m_curlevel]->GetKey() == tail->GetKey())))
            m_curlevel--;
        return true;
    }
    else
    {
        return false;
    }
}

template <class K, class V>
V* SkipList<K, V>::Retrieve(K* key)
{
    int h = 0;
    SkipNode<K, V>** update = new SkipNode<K, V>* [m_maxlevel+1];
    SkipNode<K, V>* curr = head;
    K* cmp;
    
    for (h = m_curlevel; h >= 1; h--)
    {
        cmp = curr->m_forwardnodes[h]->GetKey();
        while (*cmp < *key)
        {
            curr = curr->m_forwardnodes[h];
            cmp = curr->m_forwardnodes[h]->GetKey();
        }
        update[h] = curr;
    }
    
    curr = curr->m_forwardnodes[1];
    cmp = curr->GetKey();
    if (*cmp == *key)
    {
        return curr->GetObj();
    }
    else
    {
        return nullptr;
    }
}

template <class K, class V>
void SkipList<K, V>::Dump(ofstream& of)
{
    SkipNode<K, V>* curr;
    curr = head;
    while (curr != tail)
    {
        if (curr == head)
            of << "There's the head node!" << endl << flush;
        else
            of << "Next node holds key: " << curr->GetKey() << endl << flush;
        curr = curr->m_forwardnodes[1];
    }
    of << "There's the tial node!" << endl << flush;
}

template <class K, class V>
void SkipList<K, V>::Dump()
{
    SkipNode<K, V>* curr;
    curr = head;
    while (curr != tail)
    {
        if (curr == head)
            cout << "There's the head node!" << endl << flush;
        else
            cout << "Next node holds key: " << *(curr->GetKey()) << endl << flush;
        curr = curr->m_forwardnodes[1];
    }
    cout << "There's the tial node!" << endl << flush;
}

#endif
