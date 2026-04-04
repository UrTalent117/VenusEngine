# Venus Engine

Venus Engine 是一个基于 Lua 的轻量级图形引擎，采用组件化架构，支持实时读取 Lua 脚本文件。

## 核心功能

- **组件化架构**：所有对象都是 `Obj` 类的实例，通过模板函数 `Component` 添加组件
- **Lua 脚本支持**：实时读取目录下的 `script.lua` 文件，支持动态修改
- **预设组件**：包含 `Line`、`Circle` 和 `VenusLogo` 等预设组件
- **Windows 图形绘制**：使用 Windows API 进行图形绘制
- **跨目录运行**：将 exe 文件复制到不同目录，读取对应目录下的 `script.lua` 文件

## 目录结构

```
VenusEngine/
├── src/
│   ├── obj.h          # 核心 Obj 类定义
│   ├── components.h   # 内置组件定义
│   ├── graphics.h     # 图形库实现
│   └── main.cpp       # 主程序
├── README             # 本文档
├── script.lua         # 示例脚本
└── VenusEngine.exe    # 编译后的可执行文件
```

## 快速开始

### 1. 环境准备

- Windows 操作系统
- C++11 或更高版本的编译器
- Lua 5.5 库文件（编译时需要）

### 2. 编译项目

下载Lua的二进制文件，选择动态版本。将压缩包解压，把liblua55.a文件和include文件下的文件全部复制到VenusEngine目录下（不是src目录下，一下以Lua5.5为例）

```
lua-5.5.0_Win64_dllw6_lib/
├── include/
│   ├── lua.h              # Lua 头文件
│   ├── lauxlib.h          # Lua 辅助库头文件
│   ├── lualib.h           # Lua 标准库头文件
│   ├── lua.hpp            # Lua C++ 包装
│   └── luaconf.h          # Lua 配置头文件
├── liblua55.a
├── lua55.dll
```

使用以下命令编译项目：

```bash
g++ -std=c++11 -I. src\main.cpp -o VenusEngine.exe liblua55.a -lgdi32
```

### 3. 运行引擎

1. 创建一个包含 `script.lua` 和 `lua55.dll` 文件的目录
2. 将 `VenusEngine.exe` 复制到该目录
3. 运行 `VenusEngine.exe` 即可执行脚本

## API 文档

### Lua API

#### 核心函数

- `obj_new()`: 创建一个新的对象
- `obj_component(obj, type, ...)`: 为对象添加组件
  - `obj`: 对象实例
  - `type`: 组件类型（"Line", "Circle", "VenusLogo"）
  - `...`: 组件参数
- `obj_drawAll(obj)`: 绘制对象的所有组件
- `obj_eraseAll(obj)`: 擦除对象的所有组件
- `clear()`: 清空屏幕
- `present()`: 显示图形

#### 组件类型

1. **Line**
   - 参数：x1, y1, x2, y2
   - 功能：绘制一条线段

2. **Circle**
   - 参数：x, y, radius
   - 功能：绘制一个圆形

### C++ API

#### 核心类

1. **Graphics**
   - 功能：图形绘制类，使用 Windows API 进行绘制
   - 方法：`clear()`, `drawLine()`, `drawCircle()`, `present()`, `processEvents()`

2. **Component**
   - 功能：组件基类
   - 方法：`draw()`, `erase()`

3. **Obj**
   - 功能：对象类，管理组件
   - 方法：`component<T>()` (模板函数), `drawAll()`, `eraseAll()`

## 使用示例

### 示例脚本

```lua
-- 清空屏幕
clear()

-- 创建对象
local obj = obj_new()

-- 添加线段
obj_component(obj, "Line", 100, 100, 700, 500)

-- 添加圆形
obj_component(obj, "Circle", 400, 300, 100)

-- 绘制所有组件
obj_drawAll(obj)

-- 显示图形
present()
```

### 自定义组件

要添加自定义组件，需要：

1. 在 `components.h` 文件中定义新的组件类
2. 在 `main.cpp` 文件的 `l_obj_component` 函数中添加组件类型的处理
3. 引擎默认绘制白色，可以在 `graphics.h` 文件中传参修改

## 注意事项

- 本引擎仅在 Windows 平台上运行，因为使用了 Windows API 进行图形绘制
- 运行时需要确保目录下存在 `script.lua` 文件
- 自定义组件需要重新编译引擎

## 许可证

MIT License
