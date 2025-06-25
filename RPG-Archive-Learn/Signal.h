#pragma once

#include <vector>
#include <functional>

/// <summary>
/// 信号类模板
/// </summary>
template <typename... Args>
class Signal
{
public:
    /// <summary>
    /// 连接槽函数
    /// </summary>
    /// <param name="slot"></param>
    void Connect(std::function<void(Args...)> slot)
    {
        _slots.push_back(slot);
    }

    /// <summary>
    /// 触发信号
    /// </summary>
    /// <param name="...args"></param>
    void Emit(Args... args)
    {
        for (auto& slot : _slots)
        {
            slot(args...);
        }
    }

private:
    std::vector<std::function<void(Args...)>> _slots;
};

