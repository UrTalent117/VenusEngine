#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "lua.hpp"
#include "obj.h"
#include "components.h"

static Graphics* gGraphics = nullptr;

static int l_obj_new(lua_State* L) {
    Obj* obj = new Obj(gGraphics);
    lua_pushlightuserdata(L, obj);
    return 1;
}

static int l_obj_component(lua_State* L) {
    Obj* obj = static_cast<Obj*>(lua_touserdata(L, 1));
    const char* type = lua_tostring(L, 2);
    
    if (strcmp(type, "Line") == 0) {
        int x1 = lua_tointeger(L, 3);
        int y1 = lua_tointeger(L, 4);
        int x2 = lua_tointeger(L, 5);
        int y2 = lua_tointeger(L, 6);
        obj->component<Line>(x1, y1, x2, y2);
    } else if (strcmp(type, "Circle") == 0) {
        int x = lua_tointeger(L, 3);
        int y = lua_tointeger(L, 4);
        int radius = lua_tointeger(L, 5);
        obj->component<Circle>(x, y, radius);
    } else {
        std::cerr << "Error: Object Component not found";
    }
    
    return 0;
}

static int l_obj_drawAll(lua_State* L) {
    Obj* obj = static_cast<Obj*>(lua_touserdata(L, 1));
    obj->drawAll();
    return 0;
}

static int l_obj_eraseAll(lua_State* L) {
    Obj* obj = static_cast<Obj*>(lua_touserdata(L, 1));
    obj->eraseAll();
    return 0;
}

static int l_clear(lua_State* L) {
    if (gGraphics) {
        gGraphics->clear();
    }
    return 0;
}

static int l_present(lua_State* L) {
    if (gGraphics) {
        gGraphics->present();
    }
    return 0;
}

int main() {
    Graphics graphics(800, 600);
    gGraphics = &graphics;
    
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    
    lua_register(L, "obj_new", l_obj_new);
    lua_register(L, "obj_component", l_obj_component);
    lua_register(L, "obj_drawAll", l_obj_drawAll);
    lua_register(L, "obj_eraseAll", l_obj_eraseAll);
    lua_register(L, "clear", l_clear);
    lua_register(L, "present", l_present);
    
    std::ifstream file("script.lua");
    if (!file) {
        std::cerr << "Error: script.lua not found" << std::endl;
        return 1;
    }
    
    std::string script((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    
    if (luaL_dostring(L, script.c_str())) {
        std::cerr << "Error: " << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1);
    }
    
    bool running = true;
    while (running) {
        running = graphics.processEvents();
    }
    
    lua_close(L);
    return 0;
}
