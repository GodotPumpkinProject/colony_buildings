

#include "colony_buildings/CBuildingWorldBase.h"

Vector<Ref<CJobRoleCount>> CBuildingWorld_SimpleJobs::get_job_role_list1() const
{
    return jobRoleList;
}

void CBuildingWorld_SimpleJobs::set_job_role_list1(const Vector<Ref<CJobRoleCount>>& job_role_list)
{
    jobRoleList = job_role_list;
}

Vector<Ref<CColonist>> CBuildingWorld_SimpleJobs::get_colonists_employed() const
{
    return colonistsEmployed;
}

void CBuildingWorld_SimpleJobs::set_colonists_employed(const Vector<Ref<CColonist>>& colonists_employed)
{
    colonistsEmployed = colonists_employed;
}

void CBuildingWorld_SimpleJobs::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("set_job_role_as_typed_array", "job_list"), &CBuildingWorld_SimpleJobs::set_job_role_as_typed_array);
    ClassDB::bind_method(D_METHOD("get_job_role_as_typed_array"), &CBuildingWorld_SimpleJobs::get_job_role_as_typed_array);
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "job_list", PROPERTY_HINT_ARRAY_TYPE, MAKE_RESOURCE_TYPE_HINT("CJobRoleCount")), 
    "set_job_role_as_typed_array", "get_job_role_as_typed_array");
}


Vector<Ref<CJobRoleCount>> CBuildingWorld_SimpleJobs::get_job_role_list() const
{
    return jobRoleList;
}

void CBuildingWorld_SimpleJobs::set_job_role_list(const Vector<Ref<CJobRoleCount>>& job_role_list)
{
    jobRoleList = job_role_list;
}

TypedArray<CJobRoleCount> CBuildingWorld_SimpleJobs::get_job_role_as_typed_array()
{
    TypedArray<CJobRoleCount> returnList = {};
    for (auto r : this->jobRoleList)
    {
        returnList.append(r);
    }
    return returnList;
}

void CBuildingWorld_SimpleJobs::set_job_role_as_typed_array(const TypedArray<CJobRoleCount> newList)
{
    this->jobRoleList = {};
    for (int i = 0; i < newList.size(); ++i)
    {
        this->jobRoleList.append(newList[i]);
    }
}


bool CBuildingWorld_SimpleJobs::has_spare_jobs_by_type(Ref<CJobRole> job_role)
{

    if (job_role == NULL){ return false; }
    for (auto checkJob : this->get_job_role_list())
    {
        if (checkJob->get_job() == job_role)
        {
            int total_jobs = 0;
            for (auto checkColonist : this->colonistsEmployed)
            {
                if (checkColonist->GetJob() == job_role){ total_jobs += 1;}
            }
            
            if (total_jobs < checkJob->get_count()){ return true;}
        }
        
    }

    return false;
}
int CBuildingWorld_SimpleJobs::get_max_jobs_by_type(Ref<CJobRole> job_role)
{
    int count = 0;
    if (job_role.is_null()){ return 0;}
    
    for (auto checkJob : this->get_job_role_list()) //Iterator for multiple
        {
        if (checkJob->get_job() == job_role){ count += checkJob->get_count();}
        }
    return count;
}

int CBuildingWorld_SimpleJobs::get_spare_jobs_by_type(Ref<CJobRole> job_role)
{
    //Get max jobs, active jobs
    if (job_role.is_null()){ return 0;}
    int maxJobOfType = get_max_jobs_by_type(job_role);
    int colonistJob = 0;
    for (auto checkColonist : this->colonistsEmployed)
    {
        if (checkColonist->GetJob() == job_role){ colonistJob += 1;}
    }

    return maxJobOfType - colonistJob;
}

bool CBuildingWorld_SimpleJobs::add_colonist_to_job(Ref<CColonist> colonist)
{
    if (colonist.is_null()){ return false; }
    if (this->colonistsEmployed.find(colonist) != -1){return false;}
    
    this->colonistsEmployed.append(colonist);
    colonist->SetJobBuilding(this);
    return true;
}

bool CBuildingWorld_SimpleJobs::remove_colonist_from_job(Ref<CColonist> colonist)
{
    if (colonist.is_null()){ return false; }
    
    auto index = this->colonistsEmployed.find(colonist);
    if (index == -1){return false;}
    
    this->colonistsEmployed.remove_at(index);
    colonist->SetJobBuilding(NULL);
    return true;
}