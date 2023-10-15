#include "CBuilding.h"

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
    
    ClassDB::bind_method(D_METHOD("set_building_benifet", "building_benifet"), &CBuilding::SetBuildingBenifet);
    ClassDB::bind_method(D_METHOD("get_building_benifet"), &CBuilding::GetBuildingBenifet);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "building_benifet", PROPERTY_HINT_RESOURCE_TYPE, "CResourceCountList"), 
    "set_building_benifet", "get_building_benifet");
    
    ClassDB::bind_method(D_METHOD("set_placement_object", "placement_object"), &CBuilding::SetPlacementObject);
    ClassDB::bind_method(D_METHOD("get_placement_object"), &CBuilding::GetPlacementObject);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "placement_object", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), 
    "set_placement_object", "get_placement_object");
    
    ClassDB::bind_method(D_METHOD("set_placed_object", "placed_object"), &CBuilding::SetPlacedObject);
    ClassDB::bind_method(D_METHOD("get_placed_object"), &CBuilding::GetPlacedtObject);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "placed_object", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), 
    "set_placed_object", "get_placed_object");
    
    ClassDB::bind_method(D_METHOD("set_benifet_timer", "time"), &CBuilding::SetBenifetTimer);
    ClassDB::bind_method(D_METHOD("get_benifet_timer"), &CBuilding::GetBenifetTimer);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "benifet_timer"), 
    "set_benifet_timer", "get_benifet_timer");
}
