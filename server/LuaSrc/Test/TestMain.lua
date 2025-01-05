local M = {}


function M.init()
	print("TestMain.lua init")	

	M.testFuncCallback()
	local ret = _script.TestLuaApi.TestInteger(1)

end


function M.testFuncCallback()

	local ret = _script.TestLuaApi.TestFuncCallback(1, 2, function(a, b) 
		print("testFuncCallback a, b:", a, b)
	end )
end



M.init()

return M
