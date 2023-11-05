#include "CBuildingServer.h"

CBuildingServer::CBuildingServer()
{
    CBuildingServer::singleton = this;

}

CBuildingServer::~CBuildingServer() 
{
    ;
}

void CBuildingServer::_bind_methods()
{
    ADD_SIGNAL(MethodInfo(OnBuildingAdd));
    // ADD_SIGNAL(MethodInfo(OnBuildingChange));
    ADD_SIGNAL(MethodInfo(OnBuildingRemoved));
    ClassDB::bind_method(D_METHOD("add_building", "building"), &CBuildingServer::AddBuilding);
    ClassDB::bind_method(D_METHOD("remove_building", "building"), &CBuildingServer::RemoveBuilding);
    ClassDB::bind_method(D_METHOD("get_buildings"), &CBuildingServer::GetBuildings);
    ClassDB::bind_method(D_METHOD("get_buildings_with_spare_housing"), &CBuildingServer::GetBuildingsWithSpareHousing);
    ClassDB::bind_method(D_METHOD("get_buildings_with_spare_jobs"), &CBuildingServer::GetBuildingsWithSpareJobs);
    ClassDB::bind_method(D_METHOD("get_buildings_with_spare_jobs_by_type", "job_type"), &CBuildingServer::GetBuildingsWithSpareJobsByType);
    ClassDB::bind_method(D_METHOD("get_job_count_by_type", "job_type"), &CBuildingServer::GetJobCountByType);

}




void CBuildingServer::OnUpdate(double realTime, double gameTime)
{
    for (auto b : this->buildingList)
    {
        b->ResourceUpdate(gameTime);
    }
}

void CBuildingServer::PrePhysicsUpdate(float realTime, float gameTime)
{
    //flecs_world->run_pipeline(pipeline_prePhysicsUpdate, realTime);
}

void CBuildingServer::PhysicsUpdate(float realTime, float gameTime)
{
    //flecs_world->run_pipeline(pipeline_physicsUpdate, realTime);
}

void CBuildingServer::PostPhysicsUpdate(float realTime, float gameTime)
{
    //flecs_world->run_pipeline(pipeline_postPhysicsUpdate, realTime);
}

void CBuildingServer::PreRenderUpdate(float realTime, float gameTime)
{
    //flecs_world->run_pipeline(pipeline_preRenderUpdate, realTime);
}

void CBuildingServer::PostUpdate(float realTime, float gameTime)
{
    //flecs_world->run_pipeline(pipeline_postUpdate, realTime);
}

void CBuildingServer::AddBuilding(CBuildingWorld* newBuilding)
{
    //Check if building exists
    if (newBuilding == NULL)
    {
        print_error("Building must be real to be added to server");
        return;
    }
     if (newBuilding->get_building().is_null())
     {
         //print_error("Building must have building resource type");
         return;
     }
    
     // Check if building already exists
     auto foundIndex = this->buildingList.find(newBuilding);
     if (foundIndex != -1)
     {
         //print_error("Building Server : BUILDING NOT FOUND.");
         return;
     }

    // Builing is presumed safe to add.
    this->buildingList.append(newBuilding);
    
    emit_signal(OnBuildingAdd);
}

void CBuildingServer::RemoveBuilding(CBuildingWorld* newBuilding)
{
    if (newBuilding == NULL)
    {
        //print_error("Building must be real to be added to server");
        return;
    }
     if (newBuilding->get_building().is_null())
     {
         //print_error("Building must have building resource type.");
         return;
     }
    
     // Check if building already exists
     auto foundIndex = this->buildingList.find(newBuilding);
     if (foundIndex != -1)
     {
         //print_error("Building must not have been added to servers.");
         return;
     }

    // Builing is presumed safe to add.
    this->buildingList.remove_at(foundIndex);
    
    emit_signal(OnBuildingRemoved);
}

Array CBuildingServer::GetBuildings()
{
    Array returnList = {};
    for (auto a : this->buildingList)
    {
        returnList.append(a);
    }
    return returnList;
}

Array CBuildingServer::GetBuildingsWithSpareHousing()
{
    Array returnList = {};
    for (auto a : this->buildingList)
    {
        if (a->HasHousingCapacity())
        {
            returnList.append(a);    
        }
    }
    return returnList;
}

Array CBuildingServer::GetBuildingsWithSpareJobs()
{
    Array returnList = {};
    for (auto a : this->buildingList)
    {
        if (a->HasJobCapacity())
        {
            returnList.append(a);    
        }
    }
    return returnList;
}

Array CBuildingServer::GetBuildingsWithSpareJobsByType(Ref<CJobRole> jobRole)
{
    Array returnList = {};
    for (auto a : this->buildingList)
    {
        if (a->HasJobCapacityByType(jobRole))
        {
            returnList.append(a);    
        }
    }
    return returnList;
}

int CBuildingServer::GetJobCountByType(Ref<CJobRole> jobRole)
{
    int count = 0;
    for (auto a : this->buildingList)
    {
        count += a->JobCountByType(jobRole);
    }
    return count;
}


