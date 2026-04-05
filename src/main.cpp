#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "lua.hpp"
#include "obj.h"
#include "components.h"

static Graphics* gGraphics = nullptr;
static int gWidth = 800;
static int gHeight = 600;
static const char* gTitle = "Venus Engine";
static bool gIsFirstRun = true;

static int l_obj_new(lua_State* L) {
    if (!gGraphics) {
        return 0;
    }
    Obj* obj = new Obj(gGraphics);
    lua_pushlightuserdata(L, obj);
    return 1;
}

static int l_obj_component(lua_State* L) {
    Obj* obj = static_cast<Obj*>(lua_touserdata(L, 1));
    const char* type = lua_tostring(L, 2);
    
    if (strcmp(type, "Line") == 0) {
        if (!gGraphics) {
            return 0;
        }
        int x1 = lua_tointeger(L, 3);
        int y1 = lua_tointeger(L, 4);
        int x2 = lua_tointeger(L, 5);
        int y2 = lua_tointeger(L, 6);
        int R = lua_tointeger(L, 7);
        int G = lua_tointeger(L, 8);
        int B = lua_tointeger(L, 9);
        obj->component<Line>(x1, y1, x2, y2, R, G, B);
    } else if (strcmp(type, "Circle") == 0) {
        if (!gGraphics) {
            return 0;
        }
        int x = lua_tointeger(L, 3);
        int y = lua_tointeger(L, 4);
        int radius = lua_tointeger(L, 5);
        int R = lua_tointeger(L, 6);
        int G = lua_tointeger(L, 7);
        int B = lua_tointeger(L, 8);
        obj->component<Circle>(x, y, radius, R, G, B);
    } else if (strcmp(type, "Window") == 0) {
        int width = lua_tointeger(L, 3);
        int height = lua_tointeger(L, 4);
        const char* title = lua_tostring(L, 5);
        gWidth = width;
        gHeight = height;
        gTitle = title;
        if (gGraphics) {
            obj->component<Window>(width, height, title);
        }
    } else {
        std::cerr << "Error: Object Component : " << type << " not found" << std::endl;
    }
    
    return 0;
}

static int l_obj_drawAll(lua_State* L) {
    if (!gGraphics) {
        return 0;
    }
    Obj* obj = static_cast<Obj*>(lua_touserdata(L, 1));
    obj->drawAll();
    return 0;
}

static int l_obj_eraseAll(lua_State* L) {
    if (!gGraphics) {
        return 0;
    }
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

static int l_print(lua_State* L) {
    if (!gIsFirstRun) {
        const char* message = lua_tostring(L, 1);
        std::cout << message << std::endl;
    }
    return 0;
}

int main() {
    // 首先创建Lua状态
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    
    // 注册函数
    lua_register(L, "obj_new", l_obj_new);
    lua_register(L, "obj_component", l_obj_component);
    lua_register(L, "obj_drawAll", l_obj_drawAll);
    lua_register(L, "obj_eraseAll", l_obj_eraseAll);
    lua_register(L, "clear", l_clear);
    lua_register(L, "present", l_present);
    lua_register(L, "print", l_print);
    
    // 读取脚本文件
    std::ifstream file("script.lua");
    if (!file) {
        std::cerr << "Error: script.lua not found" << std::endl;
        return 1;
    }
    
    std::string script((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    
    // 第一次执行脚本，只处理窗口配置
    if (luaL_dostring(L, script.c_str())) {
        std::cerr << "Error: " << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1);
    }
    
    // 标记第一次执行完成
    gIsFirstRun = false;
    
    // 根据脚本中的配置创建Graphics对象
    Graphics graphics(gWidth, gHeight, gTitle);
    gGraphics = &graphics;
    
    // 第二次执行脚本，处理所有操作
    if (luaL_dostring(L, script.c_str())) {
        std::cerr << "Error: " << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1);
    }
    
    // 主循环
    bool running = true;
    while (running) {
        running = graphics.processEvents();
    }
    
    lua_close(L);
    return 0;
}
