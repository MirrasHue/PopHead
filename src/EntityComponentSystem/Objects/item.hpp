#pragma once

#include "EntityComponentSystem/object.hpp"

namespace ph{

class Item : public Object
{
public:
    void pickUp();

private:
    //std::unique_ptr<Item::Item> mItem;
};


}