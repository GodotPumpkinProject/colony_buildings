#pragma once

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
    Ref<CVisualDescription> buildingDescription;
    
    //Building 3D

    //Buiding Cost
    Ref<CResourceCountList> buildingCost;
    Ref<CResourceCountList> buildingBenifet;
    float benifetTime;
    
    Ref<PackedScene> placementObject;
    
    Ref<PackedScene> placedObject;
    
    // Colonist support to come later.
    
    // List for OnUdpate?
    

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
    CBuilding()
    {
    };

    ~CBuilding() override
    {
    };
};
