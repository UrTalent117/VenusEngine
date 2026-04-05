-- Example Lua script for Venus Engine

-- Clear the screen
clear()

-- Create a new object
local obj = obj_new()

-- Add a window component (customizable)
obj_component(obj, "Window", 1024, 768, "Venus Engine - Custom Window")

-- Add a line component
obj_component(obj, "Line", 100, 100, 900, 600, 255, 0, 0)

-- Add a circle component
obj_component(obj, "Circle", 512, 384, 150, 0, 255, 0)

-- Draw all components
obj_drawAll(obj)

-- Display the graphics
present()

print("Script executed successfully!")