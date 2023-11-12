#pragma once


#include "CBuilding.h"
//#include "CBuildingWorldBase.h"

#include "CBuildingWorldBase.h"
#include "servers/update_loop_server.h"

class CBuildingServer : public UpdateServer {
    GDCLASS(CBuildingServer, UpdateServer);

    Vector<CBuildingWorldBase*> buildingList;
    static void _bind_methods();
    
public:
    void OnUpdate(double realTime, double gameTime) override;
    virtual void PrePhysicsUpdate(float realTime, float gameTime);
    virtual void PhysicsUpdate(float realTime, float gameTime);
    virtual void PostPhysicsUpdate(float realTime, float gameTime);
    virtual void PreRenderUpdate(float realTime, float gameTime);
    virtual void PostUpdate(float realTime, float gameTime);

    void AddBuilding(CBuildingWorldBase* newBuilding);
    
    void RemoveBuilding(CBuildingWorldBase* newBuilding);

    Array GetBuildings();

    Array GetBuildingsWithSpareHousing();

    //Array GetBuildingsWithSpareJobs();

    Array GetBuildingsWithSpareJobsByType(Ref<CJobRole> jobRole);

    int GetJobCountByType(Ref<CJobRole> jobRole);
    // SIGNALS
    /// \brief Called when building is added to building server. 
    inline static const String OnBuildingAdd = "on_building_add";
    
    /// \brief Called when buildng is changed. NOT IMPLEMENTED.
    // static const String OnBuildingChange = "on_building_change";
    
    /// \brief Called when building is removed from building server. 
    inline static const String OnBuildingRemoved = "on_building_removed";
    
    inline static CBuildingServer *singleton ;
    static CBuildingServer *get_singleton(){
        return CBuildingServer::singleton;
    }
    
    CBuildingServer();
    ~CBuildingServer();
};
