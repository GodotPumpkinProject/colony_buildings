#include "colony_buildings/CBuildingWorldBase.h"


int CBuildingWorld_Housing::get_housing_max() const
{
    return housingMax;
}

void CBuildingWorld_Housing::set_housing_max(const int housing_max)
{
    housingMax = (housing_max >= 0)? housing_max : 0;
    while (this->housedColonists.size() > housingMax)
    {
        this->housedColonists[this->housedColonists.size()]->SetHousing(NULL);
    }
}

void CBuildingWorld_Housing::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("set_housing_max", "newHousingMax"), &CBuildingWorld_Housing::set_housing_max);
    ClassDB::bind_method(D_METHOD("get_housing_max"), &CBuildingWorld_Housing::get_housing_max);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "housing_max"), "set_housing_max", "get_housing_max");
}

void CBuildingWorld_Housing::on_tick(float unit_ratio, float ratio)
{
    CBuildingWorldBase::on_tick(unit_ratio, ratio);
}

bool CBuildingWorld_Housing::has_spare_housing()
{
    return this->housingMax > this->housedColonists.size();
}

bool CBuildingWorld_Housing::add_colonist_to_housing(Ref<CColonist> colonist)
{
    if (colonist.is_null()){ return false;}
    
    auto index = this->housedColonists.find(colonist);
    if (index == -1)
    {
        this->housedColonists.insert(this->housedColonists.size(), colonist);
        return true;
    }
    return false;
}

bool CBuildingWorld_Housing::remove_colonist_from_housing(Ref<CColonist> colonist)
{
    auto index = this->housedColonists.find(colonist);
    if (index >= 0)
    {
        this->housedColonists.remove_at(index);
        return true;
    }
    return false;
}
