#include <cstdio>
#include <vector>

using namespace std;

extern "C" {
    #include <lua5.3/lua.h>
    #include <lua5.3/lauxlib.h>
    #include <lua5.3/lualib.h>
}

class IntegerArray
{
public:
    explicit IntegerArray(size_t size)
    {
        if(size <= 1)
        {
            printf("invalid size\n");
        }
        else
        {
            m_integers.resize(size);
        }
    }

    int size()
    {
        return m_integers.size();
    }

    int get_value(int index)
    {
        if(index < 0 || index >= m_integers.size())
        {
            return -1;
        }

        return m_integers[index];
    }

    void set_value(int index, int value)
    {
        if(index < 0 || index >= m_integers.size())
        {
            return ;
        }

        m_integers[index] = value;
    }

private:
    vector<int> m_integers;
};

/**
 * @param[in] size
 */
static int new_array(lua_State* L)
{
    int size = static_cast<int>(luaL_checkinteger(L, 1));

    luaL_argcheck(L, size >= 1, 1, "invalid size");

    IntegerArray* array = new IntegerArray(size);

    *(IntegerArray**)lua_newuserdata(L, sizeof(IntegerArray)) = array;
    
    return 1;
}

/**
 * @param[in] array
 * @param[in] index
 * @param[in] value
 */
static int set(lua_State* L)
{
    IntegerArray** array = (IntegerArray**)lua_touserdata(L, 1);

    int index = (int)luaL_checkinteger(L, -2);
    int value = (int)luaL_checkinteger(L, -1);
    (*array)->set_value(index, value);

    return 0;
}

/**
 * @param[in] array
 * @param[in] index
 */
static int get(lua_State* L)
{
    IntegerArray** array = (IntegerArray**)lua_touserdata(L, 1);

    int index = (int)lua_tointeger(L, -1);

    int value = (*array)->get_value(index);

    lua_pushinteger(L, value);

    return 1;
}

/**
 * @param[in] array
 */
static int size(lua_State* L)
{
    IntegerArray** array = (IntegerArray**)lua_touserdata(L, 1);

    lua_pushinteger(L, (*array)->size());

    return 1;
}

static const luaL_Reg array_lib[] = {
    {"new", new_array},
    {"set", set},
    {"get", get},
    {"size", size},
    {nullptr, nullptr}
};

extern "C" int luaopen_array(lua_State* L)
{
    luaL_newlib(L, array_lib);
    return 1;
}

