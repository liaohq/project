function containsDot(str)  
    local pos = string.find(str, "%.")  
    if pos then  
        return true  
    else  
        return false  
    end  
end  
  
-- 测试函数  
local testString1 = "hello.world"  
local testString2 = "helloworld"  
  
print(containsDot(testString1)) -- 输出: true  
print(containsDot(testString2)) -- 输出: false
