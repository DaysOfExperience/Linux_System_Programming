#pragma once
#include <functional>
#include <string>
#include "log.hpp"

typedef std::function<int(int, int)> fun_t; 

class Task
{
public:
    Task() = default;
    Task(int x, int y, fun_t func)
    : x_(x), y_(y), func_(func)
    {}
    int operator()(const std::string& name)
    {
        logMessage(NORMAL, "%s处理完成: %d+%d=%d | %s | %d", name.c_str() , x_, y_, func_(x_, y_), __FILE__, __LINE__);
    }
public:
    int x_;
    int y_;
    fun_t func_;
};