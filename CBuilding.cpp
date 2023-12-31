﻿#include "CBuilding.h"

void CBuilding::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("set_building_description", "building_description"), &CBuilding::SetBuidingDescription);
    ClassDB::bind_method(D_METHOD("get_building_description"), &CBuilding::GetBuidingDescription);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "visual_description", PROPERTY_HINT_RESOURCE_TYPE, "CVisualDescription"), 
    "set_building_description", "get_building_description");
    
    ClassDB::bind_method(D_METHOD("set_building_cost", "building_cost"), &CBuilding::SetBuildingCost);
    ClassDB::bind_method(D_METHOD("get_building_cost"), &CBuilding::GetBuildingCost);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "building_cost", PROPERTY_HINT_RESOURCE_TYPE, "CResourceCountList"), 
    "set_building_cost", "get_building_cost");
    
    ClassDB::bind_method(D_METHOD("set_placement_object", "placement_object"), &CBuilding::SetPlacementObject);
    ClassDB::bind_method(D_METHOD("get_placement_object"), &CBuilding::GetPlacementObject);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "placement_object", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), 
    "set_placement_object", "get_placement_object");
    
    ClassDB::bind_method(D_METHOD("set_placed_object", "placed_object"), &CBuilding::SetPlacedObject);
    ClassDB::bind_method(D_METHOD("get_placed_object"), &CBuilding::GetPlacedObject);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "placed_object", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), 
    "set_placed_object", "get_placed_object");
    
    // ClassDB::bind_method(D_METHOD("set_housing_slots", "slots"), &CBuilding::SetHousingSlots);
    // ClassDB::bind_method(D_METHOD("get_housing_slots"), &CBuilding::GetHousingSlots);
    // ADD_PROPERTY(PropertyInfo(Variant::INT, "housing_slots"), 
    // "set_housing_slots", "get_housing_slots");

    // ClassDB::bind_method(D_METHOD("set_job_role_list", "job_list"), &CBuilding::set_job_role_list);
    // ClassDB::bind_method(D_METHOD("get_job_role_list"), &CBuilding::get_job_role_list);
    //  ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "job_list", PROPERTY_HINT_ARRAY_TYPE, MAKE_RESOURCE_TYPE_HINT("CJobRoleCount")), 
    //  "set_job_role_list", "get_job_role_list");

}

// TypedArray<CJobRoleCount> CBuilding::get_job_role_list()
// {
//     TypedArray<CJobRoleCount> returnList = {};
//     for (auto r : this->jobRoleList)
//     {
//         returnList.append(r);
//     }
//     return returnList;
// }
//
// void CBuilding::set_job_role_list(const TypedArray<CJobRoleCount> newList)
// {
//     this->jobRoleList = {};
//     for (int i = 0; i < newList.size(); ++i)
//     {
//         this->jobRoleList.append(newList[i]);
//     }
// }

void CBuilding::OnBuildingPlaced()
{
    
}

void CBuilding::OnBuildingRemoved()
{
    
}

// void CBuilding::SetHousingSlots(const int newCount)
// {
//     this->housingSlots = newCount;
// }
//
// int CBuilding::GetTotalJobCount()
// {
//     int totalCount = 0;
//     for (auto r : this->jobRoleList)
//     {
//         totalCount += r->get_count();
//     }
//     return totalCount;
// }

//
// int CBuildingFarm::get_max_plants() const
// {
//     return maxPlants;
// }
//
// void CBuildingFarm::set_max_plants(const int max_plants)
// {
//     maxPlants = max_plants;
// }
//
// int CBuildingFarm::get_ticks_to_plant() const
// {
//     return ticksToPlant;
// }
//
// void CBuildingFarm::set_ticks_to_plant(const int ticks_to_plant)
// {
//     ticksToPlant = ticks_to_plant;
// }
//
// int CBuildingFarm::get_ticks_to_harvest() const
// {
//     return ticksToHarvest;
// }
//
// void CBuildingFarm::set_ticks_to_harvest(const int ticks_to_harvest)
// {
//     ticksToHarvest = ticks_to_harvest;
// }
//
// void CBuildingFarm::_bind_methods()
// {
//     ClassDB::bind_method(D_METHOD("set_max_plants", "max_plants"), &CBuildingFarm::set_max_plants);
//     ClassDB::bind_method(D_METHOD("get_max_plants"), &CBuildingFarm::get_max_plants);
//     ADD_PROPERTY(PropertyInfo(Variant::INT, "max_plants"), 
//     "set_max_plants", "get_max_plants");
//     
//     ClassDB::bind_method(D_METHOD("set_ticks_to_plant", "ticks_to_plant"), &CBuildingFarm::set_ticks_to_plant);
//     ClassDB::bind_method(D_METHOD("get_ticks_to_plant"), &CBuildingFarm::get_ticks_to_plant);
//     ADD_PROPERTY(PropertyInfo(Variant::INT, "ticks_to_plant"), 
//     "set_ticks_to_plant", "get_ticks_to_plant");
//     
//     ClassDB::bind_method(D_METHOD("set_ticks_to_harvest", "ticks_to_harvest"), &CBuildingFarm::set_ticks_to_harvest);
//     ClassDB::bind_method(D_METHOD("get_ticks_to_harvest"), &CBuildingFarm::get_ticks_to_harvest);
//     ADD_PROPERTY(PropertyInfo(Variant::INT, "ticks_to_harvest"), 
//     "set_ticks_to_harvest", "get_ticks_to_harvest");
//
// }