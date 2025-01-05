
local function test(t)
	for k, v in pairs(t) do
		if v ~= 2 then
			goto continue
		end

		print(k,v)


		::continue::
	end

end


test( {1,2,3})
for i=1, 1000000 do
	local a = math.floor(i*2)
end
