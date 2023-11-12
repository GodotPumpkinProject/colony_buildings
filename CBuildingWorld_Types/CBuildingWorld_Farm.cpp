#include "colony_buildings/CBuildingWorldBase.h"
#include "colony_resources/ResourceServer.h"
#include "colony_time_passage/TimePassageServer.h"

int CBuildingWorld_Farm::get_farm_plots() const
{
    return farmPlots;
}

void CBuildingWorld_Farm::set_farm_plots(const int farm_plots)
{
    farmPlots = farm_plots;
}

float CBuildingWorld_Farm::get_ticks_to_plant() const
{
    return daysToPlant;
}

void CBuildingWorld_Farm::set_ticks_to_plant(const float ticks_to_plant)
{
    daysToPlant = ticks_to_plant;
}

float CBuildingWorld_Farm::get_ticks_to_harvest() const
{
    return daysToHarvest;
}

void CBuildingWorld_Farm::set_ticks_to_harvest(const float ticks_to_harvest)
{
    daysToHarvest = ticks_to_harvest;
}

Ref<CResourceCount> CBuildingWorld_Farm::get_food_gain() const
{
    return foodGain;
}

void CBuildingWorld_Farm::set_food_gain(const Ref<CResourceCount>& food_gain)
{
    foodGain = food_gain;
}

void CBuildingWorld_Farm::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("set_ticks_to_harvest", "ticks_to_harvest"), &CBuildingWorld_Farm::set_ticks_to_harvest);
    ClassDB::bind_method(D_METHOD("get_ticks_to_harvest"), &CBuildingWorld_Farm::get_ticks_to_harvest);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "ticks_to_harvest"), "set_ticks_to_harvest", "get_ticks_to_harvest");
    
    ClassDB::bind_method(D_METHOD("set_ticks_to_plant", "ticks_to_plant"), &CBuildingWorld_Farm::set_ticks_to_plant);
    ClassDB::bind_method(D_METHOD("get_ticks_to_plant"), &CBuildingWorld_Farm::get_ticks_to_plant);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "ticks_to_plant"), "set_ticks_to_plant", "get_ticks_to_plant");
    
    ClassDB::bind_method(D_METHOD("set_farm_plots", "farm_plots"), &CBuildingWorld_Farm::set_farm_plots);
    ClassDB::bind_method(D_METHOD("get_farm_plots"), &CBuildingWorld_Farm::get_farm_plots);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "farm_plots"), "set_farm_plots", "get_farm_plots");
    
    ClassDB::bind_method(D_METHOD("set_food_gain", "food_gain"), &CBuildingWorld_Farm::set_food_gain);
    ClassDB::bind_method(D_METHOD("get_food_gain"), &CBuildingWorld_Farm::get_food_gain);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "food_gain",PROPERTY_HINT_RESOURCE_TYPE, "CResourceCount"), "set_food_gain", "get_food_gain");
}

void CBuildingWorld_Farm::on_tick(float unit_ratio, float ratio)
{
    CBuildingWorldBase::on_tick(unit_ratio, ratio);

    auto timeServer = TimePassageServer::get_singleton();
    if (timeServer == NULL){ return;}

    this->dayCounter += unit_ratio * this->get_colonists_employed().size();
    if (timeServer->is_grow_season())
    {
        while (dayCounter >daysToPlant )
        {
            dayCounter -= daysToPlant;
            if (plantedSeeds < farmPlots)
            {
                print_line("Seeds planted = " + itos(plantedSeeds));
                plantedSeeds += 1;
            }
        }
    }
    else if (timeServer->is_harvest_season())
    {
        while (dayCounter >daysToHarvest )
        {
            dayCounter -= daysToHarvest;
            if (plantedSeeds > 0)
            {
                plantedSeeds += 1;
                ColonyResourceServer::get_singleton()->AddResource(foodGain->get_resource(), foodGain->get_count());
            }
        }
    }
    else
    {
        dayCounter = 0;
        plantedSeeds = 0;
    }
    //print_line("on_tick for farm");
}


