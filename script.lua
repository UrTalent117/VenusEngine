-- Example Lua script for Venus Engine

-- Clear the screen
clear()

-- Create a new object
local obj = obj_new()

-- Add a line component
obj_component(obj, "Line", 100, 100, 700, 500, 255, 0, 0)

-- Add a circle component
obj_component(obj, "Circle", 400, 300, 100, 0, 255, 0)

-- Draw all components
obj_drawAll(obj)

-- Display the graphics
present()

print("Script executed successfully!")
