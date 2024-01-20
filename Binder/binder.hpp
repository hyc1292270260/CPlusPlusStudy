#include <any>
#include <iostream>
#include <map>
#include <typeinfo>
#include <functional>
using namespace std;

template <class T>
class Binder {
public:
	using FuncType = std::function<void(T*, void*)>;
	using StaticFuncType = std::function<void(void*)>;

private:
	std::map<std::string, size_t> vars;
	std::map<std::string, FuncType> funcs;
	std::map<std::string, StaticFuncType> staticFuncs;

public:
	void bindVar(std::string varName, size_t offet) {
		vars[varName] = offet;
	}

	void bindFunc(std::string funcName, FuncType func) {
		funcs[funcName] = func;
	}

	void bindStaticFunc(std::string funcName, StaticFuncType staticFunc) {
		staticFuncs[funcName] = staticFunc;
	}

public:
	template <typename T1>
	T1* findVar(void* obj, std::string varName)
	{
		if (vars.find(varName) == vars.end())
		{
			return nullptr;
		}
		size_t offset = vars.at(varName);
		return (T1*)((size_t)obj + offset);
	}

	void callFunc(T* obj, std::string funcName, void* params)
	{
		FuncType func = funcs.at(funcName);
		if (func)
		{
			func(obj, params);
		}
	}

	void callStaticFunc(std::string funcName, void* params)
	{
		StaticFuncType staticFunc = staticFuncs.at(funcName);
		if (staticFunc)
		{
			staticFunc(params);
		}
	}
};

// std::any_cast转换有些问题
//class Binder
//{
//public:
//    template<typename T, typename R, typename... Args>
//    void registerMemberFunction(std::string name, R(T::* f)(Args...))
//    {
//        memberFunctions[std::make_pair(typeid(T).name(), name)] = [f](T* t, Args... args) {
//            return (t->*f)(args...);
//        };
//    }
//
//    template<typename T, typename R, typename... Args>
//    void registerStaticFunction(std::string name, R(*f)(Args...))
//    {
//        staticFunctions[std::make_pair(typeid(T).name(), name)] = [f](Args... args) {
//            return (*f)(args...);
//        };
//    }
//
//    template<typename T, typename R, typename... Args>
//    R callMemberFunction(T* t, std::string name, Args... args)
//    {
//        auto it = memberFunctions.find(std::make_pair(typeid(T).name(), name));
//        if (it != memberFunctions.end())
//        {
//            auto func = std::any_cast<std::function<R(T*, Args...)>>(it->second);
//            return func(t, args...);
//        }
//        else
//        {
//            throw std::runtime_error("callMemberFunction not found");
//        }
//    }
//
//    template<typename T, typename R, typename... Args>
//    R callStaticFunction(std::string name, Args... args)
//    {
//        auto it = staticFunctions.find(std::make_pair(typeid(T).name(), name));
//        if (it != staticFunctions.end())
//        {
//            auto func = std::any_cast<std::function<R(Args...)>>(it->second);
//            return func(args...);
//        }
//        else
//        {
//            throw std::runtime_error("callStaticFunction not found");
//        }
//    }
//
//private:
//    std::map<std::pair<std::string, std::string>, std::any> memberFunctions;
//    std::map<std::pair<std::string, std::string>, std::any> staticFunctions;
//};

