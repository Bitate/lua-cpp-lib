array = package.loadlib("/home/bitate/lua-cpp-lib/build/cpp-array/libarray_lib.so", "luaopen_array")()

a = array.new(1000)

for i = 1, 1000 do
    a:set(a, i, i);
end

print(a:get(a, 10)) -- 10
print(a:get(a, 11)) -- 11
print(a:size(a))    -- 1000