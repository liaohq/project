local core =  require "libcore"

local M = {}


function M.init()
	print("init.lua init begin")
	print("curTime:", mylib.getTime())
	print("getMicroSeconds:", mylib.getMicroSeconds())
	print("clib test:", clib.test())
end



M.init()


