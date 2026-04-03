#pragma once
#include <map>
#include <string>
#include <memory>

class Component {
public:
    virtual ~Component() = default;
    virtual void draw() = 0;
    virtual void erase() = 0;
};

class Obj {
private:
    std::map<std::string, std::unique_ptr<Component>> components;

public:
    template <typename T, typename... Args>
    T* component(Args&&... args) {
        std::string typeName = typeid(T).name();
        auto it = components.find(typeName);
        if (it != components.end()) {
            return static_cast<T*>(it->second.get());
        }
        auto comp = std::make_unique<T>(std::forward<Args>(args)...);
        T* ptr = comp.get();
        components[typeName] = std::move(comp);
        return ptr;
    }

    void drawAll() {
        for (auto& [name, comp] : components) {
            comp->draw();
        }
    }

    void eraseAll() {
        for (auto& [name, comp] : components) {
            comp->erase();
        }
    }
};
