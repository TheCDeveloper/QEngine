#include <QEngine/Instance.hpp>
#include <algorithm>


void QEngine::Instance::parent(Instance* newParent) {
    if (m_ParentLocked) {
        return;
    }
    
    if (m_Parent) {
        auto& list = m_Parent->m_Children;
        list.erase(std::remove(list.begin(), list.end(), this), list.end());
    }
  
    m_Parent = newParent;
    newParent->m_Children.push_back(this);
}


QEngine::Instance* QEngine::Instance::child(std::string_view name) const {
    for (auto& instance : m_Children) {
        if (instance->m_Name == name) {
            return instance;
        }
    }
  
    return nullptr;
}
