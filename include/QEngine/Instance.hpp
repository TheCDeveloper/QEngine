#pragma once
#include <string>
#include <vector>


namespace QEngine {

class Instance {
public:
    Instance() : m_Name("Instance"), m_ParentLocked(false), m_Parent(nullptr) {}
    Instance(Instance* parent);

    virtual ~Instance() = default;


    virtual const char* className() const { return "Instance"; }

    std::string_view name() const { return m_Name; }
    void name(std::string_view newName) { m_Name = newName; }

    Instance* parent() const { return m_Parent; }
    void parent(Instance* newParent);

    Instance* child(std::string_view name) const;
    const std::vector<Instance*>& children() const { return m_Children; }


protected:
    std::string m_Name;

    bool m_ParentLocked;
    Instance* m_Parent;
    std::vector<Instance*> m_Children;
};

}
