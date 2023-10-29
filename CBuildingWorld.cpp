#include "CBuildingWorld.h"

#include "CBuildingServer.h"
#include "colony_colonists/CColonist.h"
#include "colony_resources/ResourceServer.h"

Vector<Ref<CColonist>> CBuildingWorld::get_colonist_workers() const
{
    return colonistWorkers;
}

void CBuildingWorld::set_colonist_workers(const Vector<Ref<CColonist>>& colonist_workers)
{
    colonistWorkers = colonist_workers;
}

Vector<Ref<CColonist>> CBuildingWorld::get_colonist_housed() const
{
    return colonistHoused;
}

void CBuildingWorld::set_colonist_housed(const Vector<Ref<CColonist>>& colonist_housed)
{
    colonistHoused = colonist_housed;
}

void CBuildingWorld::_bind_methods()
{
    GDVIRTUAL_BIND(on_world_enter);
    GDVIRTUAL_BIND(on_world_exit);
    GDVIRTUAL_BIND(on_resource_complete);

    ClassDB::bind_method(D_METHOD("set_building", "building"), &CBuildingWorld::set_building);
    ClassDB::bind_method(D_METHOD("get_building"), &CBuildingWorld::get_building);
    ClassDB::bind_method(D_METHOD("get_building"), &CBuildingWorld::get_building);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "building", PROPERTY_HINT_RESOURCE_TYPE, "CBuilding"), 
    "set_building", "get_building");

    
    ClassDB::bind_method(D_METHOD("add_worker", "colonist"), &CBuildingWorld::AddWorker);
    ClassDB::bind_method(D_METHOD("remove_worker", "colonist"), &CBuildingWorld::RemoveWorker);

    ClassDB::bind_method(D_METHOD("add_housed_colonist", "colonist"), &CBuildingWorld::AddHousedColonist);
    ClassDB::bind_method(D_METHOD("remove_housed_colonist", "colonist"), &CBuildingWorld::RemoveHousedColonist);

    ClassDB::bind_method(D_METHOD("has_housing_capacity"), &CBuildingWorld::HasHousingCapacity);

    ClassDB::bind_method(D_METHOD("has_job_capacity_by_type", "job_type"), &CBuildingWorld::HasJobCapacityByType);

    ClassDB::bind_method(D_METHOD("get_job_count_by_type", "job_type"), &CBuildingWorld::JobCountByType);

    
}

void CBuildingWorld::_notification(int p_notification)
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
               this->on_world_enter();
                
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
                this->on_world_exit();
            }break;
    }
}

void CBuildingWorld::ResourceUpdate(float gameTimeDelta)
{
    while (this->building == NULL)
    {
        resourceUpdateTimer = 0;
        return;
    }
    resourceUpdateTimer += gameTimeDelta;
    
    auto maxJobSlots = this->building->GetTotalJobCount();
    auto currentJobSlots = this->get_colonist_workers().size();
    
    while (resourceUpdateTimer >= this->building->GetBenifetTimer() * (1 + maxJobSlots - currentJobSlots ) )
    {
        resourceUpdateTimer -= this->building->GetBenifetTimer();
        ColonyResourceServer::get_singleton()->AddResourceList(this->building->GetBuildingBenifet());
    }
}

void CBuildingWorld::AddWorker(Ref<CColonist> colonist)
{
    if (colonist.is_null()){ return; }
    
    if (this->colonistWorkers.find(colonist) == -1)
    {
        this->colonistWorkers.append(colonist);
        colonist->SetJobBuilding(this);
    }
}

void CBuildingWorld::RemoveWorker(Ref<CColonist> colonist)
{
    if (colonist.is_null()){ return; }

    auto index = this->colonistWorkers.find(colonist);
    if (index != -1)
    {
        this->colonistWorkers.remove_at(index);
        colonist->SetJobBuilding(NULL);
    }
}

void CBuildingWorld::AddHousedColonist(Ref<CColonist> colonist)
{
    if (colonist.is_null()){ return; }
    
    if (this->colonistHoused.find(colonist) == -1)
    {
        this->colonistHoused.append(colonist);
        colonist->SetHousing(this);
    }
}

void CBuildingWorld::RemoveHousedColonist(Ref<CColonist> colonist)
{
    if (colonist.is_null()){ return; }
    
    auto index = this->colonistHoused.find(colonist);
    if (index != -1)
    {
        this->colonistHoused.remove_at(index);
        colonist->SetHousing(NULL);
    }
}

bool CBuildingWorld::HasHousingCapacity()
{
    if (this->building == NULL){ return false;}
    if (this->colonistHoused.size() >= this->building->GetHousingSlots()){ return false;}
    return true;
}

bool CBuildingWorld::HasJobCapacity()
{
    if (this->building == NULL){ return false;}
    int total_jobs = 0;
    for (auto i = 0 ; i < this->building->GetJobRoleList().size(); ++i)
    {
        // TODO : Replace this with better system
        auto jobRole = Ref<CJobRoleCount>(this->building->GetJobRoleList()[i]);
        total_jobs += jobRole->get_count();
    }
    if (this->colonistWorkers.size() >= total_jobs){ return false;}
    return true;
}

bool CBuildingWorld::HasJobCapacityByType(Ref<CJobRole> jobRole)
{
    if (this->building == NULL){ return false;}
    if (jobRole == NULL){ return false; }
    
    for (auto i = 0 ; i < this->building->GetJobRoleList().size(); ++i)
    {
        
        // TODO : Replace this with better system
        auto foundJob = Ref<CJobRoleCount>(this->building->GetJobRoleList()[i]);
        if (foundJob->get_job() == jobRole)
        {
            int total_jobs = 0;
            for (auto j = 0 ; j < this->colonistWorkers.size() ; ++j)
            {
                if (this->colonistWorkers[j]->GetJob() == jobRole){ total_jobs += 1;}
            }
            if (total_jobs < foundJob->get_count()){ return true;}
        }
    }
    return false;
}

int CBuildingWorld::JobCountByType(Ref<CJobRole> jobRole)
{
    if (this->building == NULL){ return 0;}
    if (jobRole == NULL){ return 0; }
    int total_jobs = 0;
    for (auto i = 0 ; i < this->building->GetJobRoleList().size(); ++i)
    {
        
        auto foundJob = Ref<CJobRoleCount>(this->building->GetJobRoleList()[i]);
        if (foundJob->get_job() == jobRole)
        {
            total_jobs += foundJob->get_count();
        }
    }
    return total_jobs;
}

