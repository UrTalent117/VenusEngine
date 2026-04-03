# Venus Engine

Venus Engine 是一个轻量级的解释型游戏/图形引擎，使用 C++ 开发，支持通过 Lua 脚本进行配置和扩展。

## 简介

Venus Engine 不是 GeoGebra，而是一个独立的引擎项目。它的设计灵感来源于 Unity，采用组件化架构，所有对象都是 `Obj` 类的实例，通过模板函数 `Component` 来添加和管理组件。

## 核心功能

- **组件化架构**：所有对象都是 `Obj` 类的实例，通过模板函数 `Component` 添加组件
- **Lua 脚本支持**：通过解释型执行，可在不同目录下使用不同的 lua 文件
- **内置组件**：包含 `SetLine`、`Circle` 等基本图形组件
- **自定义组件**：支持用户自定义组件类型
- **跨平台**：可编译为独立的可执行文件

## 目录结构

```
VenusEngine/
├── src/
│   ├── obj.h          # 核心 Obj 类定义
│   ├── components.h   # 内置组件定义
│   └── main.cpp       # 主程序，包含 Lua 解释器
├── build.bat          # 编译脚本
├── script.lua         # 示例 Lua 脚本
└── README.md          # 本文档
```

## 使用方法

### 1. 环境配置

- 需要安装 Lua 5.4 或 5.5
- 需要安装 MSVC 或 MinGW 编译器
- 在 `build.bat` 中配置 Lua 路径：
  ```bat
  set LUA_INC=D:\lua-5.5\include
  set LUA_LIB=D:\lua-5.5
  ```

### 2. 编译项目

运行 `build.bat` 脚本编译项目，生成 `VenusEngine.exe` 可执行文件。脚本会自动检测编译器类型并选择相应的编译命令。

### 3. 运行引擎

将生成的 `VenusEngine.exe` 和相应的 Lua DLL 文件（如 lua55.dll）复制到包含 `script.lua` 文件的目录中，运行即可执行脚本。

### 4. 编写 Lua 脚本

示例脚本 `script.lua`：

```lua
-- 创建一个新对象
local obj = obj_new()

-- 添加线条组件
obj_component(obj, "SetLine", 10, 10, 100, 100)

-- 添加圆形组件
obj_component(obj, "Circle", 50, 50, 30)

-- 绘制所有组件
obj_drawAll(obj)

-- 擦除所有组件
obj_eraseAll(obj)

print("Script executed successfully!")
```

## 扩展指南

### 添加自定义组件

1. 在 `components.h` 中添加新的组件类，继承自 `Component` 类
2. 实现 `draw()` 和 `erase()` 方法
3. 在 `main.cpp` 的 `l_obj_component` 函数中添加组件类型的处理逻辑

### 自定义渲染方式

可以通过重写组件的 `draw()` 和 `erase()` 方法来实现自定义渲染逻辑。

## 技术特点

- **模板函数**：使用 C++ 模板实现组件的动态添加
- **智能指针**：使用 `std::unique_ptr` 管理组件生命周期
- **Lua 绑定**：通过 Lua C API 实现 C++ 与 Lua 的交互
- **解释型执行**：支持运行时加载和执行 Lua 脚本

## 注意事项

- 本引擎目前处于开发阶段，仅提供基本功能
- 渲染功能需要根据具体平台进行实现
- 后续版本将添加更多内置组件和功能
