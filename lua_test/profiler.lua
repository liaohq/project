function print_table(t, indent)
    indent = indent or ""
    for k, v in pairs(t) do
        if type(v) == "table" then
            print(indent .. k .. ": ")
            print_table(v, indent .. "  ")
        else
            print(indent .. k .. ": " .. tostring(v))
        end
    end
end


local beginTime = os.clock()
local randomVal

local t = {}
local random = math.random

for i = 1, 10000000 do
   randomVal = random(0, 10000)
	
   table.insert(t,i)
end


local costTime = os.clock() - beginTime
print("cost time:", costTime)


