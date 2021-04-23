//
// Created by iWong on 21/4/2021.
//

#ifndef _IMAGEMATCH_SINGLETON_H
#define _IMAGEMATCH_SINGLETON_H

template <class CObject>

class Singleton{
private:
    Singleton() = default;
    ~Singleton() = default;

public:
    static CObject* Instance();

    static void Destory();

private:
    static Singleton<CObject> *m_singleton;
    CObject m_instance;
};


template<class CObject>
Singleton<CObject> *Singleton<CObject>::m_singleton = nullptr;

template<class CObject>
CObject *Singleton<CObject>::Instance() {
    if (Singleton<CObject>::m_singleton == nullptr)
        Singleton<CObject>::m_singleton = new Singleton<CObject>();

    return &(Singleton<CObject>::m_singleton->m_instance);
}

template<class CObject>
void Singleton<CObject>::Destory()
{
    if (Singleton<CObject>::m_singleton != nullptr)
        delete Singleton<CObject>::m_singleton;
    Singleton<CObject>::m_singleton = nullptr;
}

#endif //_IMAGEMATCH_SINGLETON_H
