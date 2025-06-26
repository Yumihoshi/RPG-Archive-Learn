#pragma once

#include <iostream>

template<typename T, typename T2>
class BasePokeController
{
public:
    std::shared_ptr<T> ModelPtr;
    std::shared_ptr<T2> ViewPtr;

    BasePokeController(std::shared_ptr<T> model)
    {
        ModelPtr = model;
        ViewPtr = std::make_shared<T2>(model);
    }
};

