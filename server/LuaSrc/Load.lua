print("****************** load begin ***************** ")


local M = {}

function M.init()
	print("init")

	M.initEnv()
	M.initModule()
	--M.test()
end


function M.initEnv()
	print("init envirment")
	print("package.path:", package.path)

	package.cpath = package.cpath .. ";../Lib/?.so"
	print("package.cpath:", package.cpath)
end


function M.initModule()
	require "Init"
	require "Test.TestMain"
end


function M.test()
	local result = libcore.add(1,2);
	print("libcore add result:", result)

	local t = timeManager.GetNowTime();
	print("timeManager.GetNowTime curTime:", t)




	result = _script.libcore.add(1,2)
	print("_script.libcore add result:", result)

	t = _script.timeManager.GetNowTime();
	print("_script.timeManager.GetNowTime curTime:", t)



	result = clib_test.add(1,2)
	print("clib_test.add result:", result)
	
	t = clib_test.GetNowTime();
	print("clib_test.GetNowTime curTime:", t)


	t = clib.GetNowTime();
	print("clib.GetNowTime curTime:", t)
end











M.init()

print("***************** load end ****************")
