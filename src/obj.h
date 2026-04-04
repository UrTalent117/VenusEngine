#pragma once
#include <map>
#include <string>
#include <memory>
#include "graphics.h"

class Component {
protected:
    Graphics* graphics;

public:
    Component(Graphics* g) : graphics(g) {}
    virtual ~Component() = default;
    virtual void draw() = 0;
    virtual void erase() = 0;
};

class Obj {
private:
    std::map<std::string, std::unique_ptr<Component>> components;
    Graphics* graphics;

public:
    Obj(Graphics* g) : graphics(g) {}

    template <typename T, typename... Args>
    T* component(Args&&... args) {
        std::string typeName = typeid(T).name();
        auto it = components.find(typeName);
        if (it != components.end()) {
            return static_cast<T*>(it->second.get());
        }
        std::unique_ptr<T> comp(new T(graphics, std::forward<Args>(args)...));
        T* ptr = comp.get();
        components[typeName] = std::move(comp);
        return ptr;
    }

    void drawAll() {
        for (auto& pair : components) {
            pair.second->draw();
        }
    }

    void eraseAll() {
        for (auto& pair : components) {
            pair.second->erase();
        }
    }
};
