#pragma once

#include "colony_resources/CJobRole.h"
#include "colony_resources/CResourceList.h"
#include "core/object/object.h"
#include "core/io/resource.h"
#include "scene/resources/packed_scene.h"

/// \brief Godot Resource describing a common 'resource' such as 'wood' or 'stone'.
class CBuilding : public Resource
{
    GDCLASS(CBuilding, Resource);

    //Building Description

    //Building Icon
    Ref<CVisualDescription> buildingDescription = {};
    
    //Building 3D

    //Buiding Cost
    Ref<CResourceCountList> buildingCost = NULL;
    Ref<CResourceCountList> buildingBenifet = NULL;
    
    Vector<Ref<CJobRoleCount>> jobRoleList = {};
    
    float benifetTime = 1.0f;
    
    Ref<PackedScene> placementObject= NULL;
    
    Ref<PackedScene> placedObject= NULL;
    
    int housingSlots = 0;
    

protected:
    static void _bind_methods();

public:
    Ref<CVisualDescription> GetBuidingDescription(){ return buildingDescription;}
    void SetBuidingDescription(const Ref<CVisualDescription>& newDescription ){  buildingDescription = newDescription;}
    
    Ref<CResourceCountList> GetBuildingCost(){ return buildingCost;}
    void SetBuildingCost(const Ref<CResourceCountList>& newCost ){  buildingCost = newCost;}
        
    Ref<CResourceCountList> GetBuildingBenifet(){ return buildingBenifet;}
    void SetBuildingBenifet(const Ref<CResourceCountList>& newBenifets ){  buildingBenifet = newBenifets;}
        
    Ref<PackedScene> GetPlacementObject(){ return placementObject;}
    void SetPlacementObject(const Ref<PackedScene>& o ){  placementObject = o;}
        
    Ref<PackedScene> GetPlacedtObject(){ return placedObject;}
    void SetPlacedObject(const Ref<PackedScene>& o ){  placedObject = o;}

    float GetBenifetTimer(){ return this->benifetTime; }
    void SetBenifetTimer(const float f){ this->benifetTime = f;}

    void SetHousingSlots(const int newCount);
    int GetHousingSlots(){return this->housingSlots;}

    void SetJobRoleList(Vector<Ref<CJobRoleCount>> newList){ this->jobRoleList = newList;}
    Vector<Ref<CJobRoleCount>> GetJobRoleList(){return this->jobRoleList;}
    int GetTotalJobCount();
    TypedArray<CJobRoleCount> get_job_role_list();
    void set_job_role_list(const TypedArray<CJobRoleCount> newList);
    
    virtual void OnBuildingPlaced();
    virtual void OnBuildingRemoved();
    
    CBuilding()
    {
    };

    ~CBuilding() override
    {
    };
    
};


