-- Example Lua script for Venus Engine

-- Create a new object
local obj = obj_new()

-- Add a line component
obj_component(obj, "SetLine", 10, 10, 100, 100)

-- Add a circle component
obj_component(obj, "Circle", 50, 50, 30)

-- Draw all components
obj_drawAll(obj)

-- Erase all components
obj_eraseAll(obj)

print("Script executed successfully!")
