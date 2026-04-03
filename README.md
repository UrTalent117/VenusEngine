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

- **安装编译器**：ual Studio 带 C++ 开需要安装 MSVC（Vis发工具）或 MinGW-w64
- **准备 Lua 5.5 文件**：将以下文件放在 VenusEngine 目录下：
  - `lua.hpp`（头文件）
  - `lua55.lib`（MSVC 静态库）或 `liblua55.a`（MinGW 静态库）
  - `lua55.dll`（动态库，可选）

### 2. 编译项目

运行 `build.bat` 脚本编译项目，生成 `VenusEngine.exe` 可执行文件。脚本会：
1. 检查 Lua 头文件是否存在
2. 检测可用的编译器（MSVC 或 MinGW）
3. 根据编译器类型选择相应的编译命令
4. 编译成功后自动复制 Lua DLL 文件

### 3. 编译原理

编译过程分为以下几个步骤：
1. **预处理**：处理头文件包含和宏定义
2. **编译**：将 C++ 代码编译成目标文件（.obj 或 .o）
3. **链接**：将目标文件与 Lua 库链接成可执行文件

`build.bat` 脚本会根据检测到的编译器类型执行相应的编译命令：
- **MSVC**：使用 `cl` 命令编译，链接 `lua55.lib`
- **MinGW**：使用 `g++` 命令编译，链接 `liblua55.a`

### 4. 运行引擎

将生成的 `VenusEngine.exe` 和 `lua55.dll` 文件复制到包含 `script.lua` 文件的目录中，运行即可执行脚本。

### 5. 编写 Lua 脚本

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

### 6. 添加自定义组件

1. 在 `components.h` 中添加新的组件类，继承自 `Component` 类
2. 实现 `draw()` 和 `erase()` 方法
3. 在 `main.cpp` 的 `l_obj_component` 函数中添加组件类型的处理逻辑

### 7. 自定义渲染方式

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
