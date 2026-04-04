-- Example Lua script for Venus Engine

-- Clear the screen
clear()

-- Create a new object
local obj = obj_new()

-- Add Venus logo component (preset)
obj_component(obj, "VenusLogo", 400, 300, 200)

-- Add a line component
obj_component(obj, "SetLine", 100, 100, 700, 500)

-- Add a circle component
obj_component(obj, "Circle", 400, 300, 100)

-- Draw all components
obj_drawAll(obj)

-- Display the graphics
present()

print("Script executed successfully!")
