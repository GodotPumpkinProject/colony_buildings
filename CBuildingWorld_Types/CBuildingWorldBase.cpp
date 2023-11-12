
#include "colony_buildings/CBuildingWorldBase.h"

#include "colony_buildings/CBuildingServer.h"
#include "colony_time_passage/TimePassageServer.h"

Ref<CBuilding> CBuildingWorldBase::get_building_type() const
{
    return buildingType;
}

void CBuildingWorldBase::set_building_type(const Ref<CBuilding>& building_type)
{
    buildingType = building_type;
}

bool CBuildingWorldBase::has_spare_housing()
{
    //print_line("CBuildingWorldBase::has_spare_housing");
    return false;
}

void CBuildingWorldBase::_bind_methods()
{

    ClassDB::bind_method(D_METHOD("set_building_type", "building_type"), &CBuildingWorldBase::set_building_type);
    ClassDB::bind_method(D_METHOD("get_building_type"), &CBuildingWorldBase::get_building_type);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "building_type", PROPERTY_HINT_RESOURCE_TYPE, ("CBuilding")), "set_building_type", "get_building_type");

    ClassDB::bind_method(D_METHOD("has_spare_housing"), &CBuildingWorldBase::has_spare_housing);
    


    ClassDB::bind_method(D_METHOD("has_spare_jobs"), &CBuildingWorldBase::has_spare_housing);
    ClassDB::bind_method(D_METHOD("has_spare_jobs_by_type"), &CBuildingWorldBase::has_spare_jobs_by_type);
    ClassDB::bind_method(D_METHOD("get_max_jobs_by_type"), &CBuildingWorldBase::get_max_jobs_by_type);
    ClassDB::bind_method(D_METHOD("get_spare_jobs_by_type"), &CBuildingWorldBase::get_spare_jobs_by_type);
    
    ClassDB::bind_method(D_METHOD("add_colonist_to_housing", "colonist"), &CBuildingWorldBase::add_colonist_to_housing);
    ClassDB::bind_method(D_METHOD("remove_colonist_from_housing", "colonist"), &CBuildingWorldBase::remove_colonist_from_housing);
    ClassDB::bind_method(D_METHOD("add_colonist_to_job", "colonist"), &CBuildingWorldBase::add_colonist_to_job);
    ClassDB::bind_method(D_METHOD("remove_colonist_from_job", "colonist"), &CBuildingWorldBase::remove_colonist_from_job);
}

void CBuildingWorldBase::_notification(int p_notification)
{
    switch (p_notification)
    {
    case NOTIFICATION_ENTER_TREE:
        {
            auto buildingServer = CBuildingServer::get_singleton();
            if (buildingServer == NULL)
            {
                print_error("Building server was not ready");
                return;
            }
            buildingServer->AddBuilding(this);
           // this->on_world_enter();
                
        } break;
    case NOTIFICATION_EXIT_TREE:
        {
            auto buildingServer = CBuildingServer::get_singleton();
            if (buildingServer == NULL)
            {
                print_error("Building server was not ready");
                return;
            }
            buildingServer->RemoveBuilding(this);
           // this->on_world_exit();
        }break;
    }
}


CBuildingWorldBase::CBuildingWorldBase()
{
    auto timeServer = TimePassageServer::get_singleton();
    if (timeServer)
    {
        timeServer->connect((TimePassageServer::sOnDayClick), callable_mp(this, &CBuildingWorldBase::on_tick));
        timeServer->connect((TimePassageServer::sOnDayPassed), callable_mp(this, &CBuildingWorldBase::on_day));
        timeServer->connect((TimePassageServer::sOnSeasonPassed), callable_mp(this, &CBuildingWorldBase::on_season));
    }
}


