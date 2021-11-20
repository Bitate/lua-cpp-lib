array = package.loadlib("/home/bitate/cpp-lua-lib/build/cpp-array/libarray_lib.so", "luaopen_array")()

a = array.new(1000)

for i = 1, 1000 do
    array.set(a, i, i);
end

print(array.get(a, 10)) -- 10
print(array.get(a, 11)) -- 11
print(array.size(a))    -- 1000