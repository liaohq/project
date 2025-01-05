local core = require "libcore"
print("core:", core)


for k,v in pairs(core.mylib) do
	print("k", k)
	print("v:", v)

end


local curTime = core.getTime()
print("curTime:", curTime)

local microSeconds = core.getMicroSeconds()
print("microSeconds:", microSeconds)
--]]
