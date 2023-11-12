#pragma once
#include "CBuilding.h"
#include "colony_colonists/CColonist.h"
#include "colony_time_passage/Season.h"
#include "scene/3d/node_3d.h"


/*
 * Problem : I have 1 data type which always pairs exactly to a specific world type.
 * This is awkward and clumsy.
 *
 * 
 **/


//class CColonist : public Resource{};

class CBuildingWorldBase : public Node3D
{
    GDCLASS(CBuildingWorldBase, Node3D);

    Ref<CBuilding> buildingType;

protected:
    static void _bind_methods();

    void _notification(int p_notification);

public:
    Ref<CBuilding> get_building_type() const;
    void set_building_type(const Ref<CBuilding>& building_type);


    //virtual bool has_spare_jobs() { return false; };
    virtual bool has_spare_jobs_by_type(Ref<CJobRole>) { return false; };
    virtual int get_max_jobs_by_type(Ref<CJobRole>) { return 0; };
    virtual int get_spare_jobs_by_type(Ref<CJobRole>) { return 0; };
    virtual bool add_colonist_to_job(Ref<CColonist>) { return false; };
    virtual bool remove_colonist_from_job(Ref<CColonist>) { return false; };

    virtual bool has_spare_housing();
    virtual bool add_colonist_to_housing(Ref<CColonist>) { return false; };
    virtual bool remove_colonist_from_housing(Ref<CColonist>) { return false; };

    virtual void on_tick(float unit_ratio, float ratio)
    {
    }

    virtual void on_day(float unit_ratio, float ratio)
    {
    }

    virtual void on_season(Ref<Season> newSeason)
    {
    }

    CBuildingWorldBase();
};

class CBuildingWorld_SimpleJobs : public CBuildingWorldBase
{
    GDCLASS(CBuildingWorld_SimpleJobs, CBuildingWorldBase);

    // Which jobs are supported in this building
    Vector<Ref<CJobRoleCount>> jobRoleList = {};
    Vector<Ref<CColonist>> colonistsEmployed = {};

public:
    Vector<Ref<CJobRoleCount>> get_job_role_list1() const;
    void set_job_role_list1(const Vector<Ref<CJobRoleCount>>& job_role_list);
    Vector<Ref<CColonist>> get_colonists_employed() const;
    void set_colonists_employed(const Vector<Ref<CColonist>>& colonists_employed);

protected:
    static void _bind_methods();
public:
    bool has_spare_jobs_by_type(Ref<CJobRole>) override;
    int get_max_jobs_by_type(Ref<CJobRole> job_role) override;
    int get_spare_jobs_by_type(Ref<CJobRole>) override;
    bool add_colonist_to_job(Ref<CColonist>) override;
    bool remove_colonist_from_job(Ref<CColonist>) override;
    
    Vector<Ref<CJobRoleCount>> get_job_role_list() const;
    void set_job_role_list(const Vector<Ref<CJobRoleCount>>& job_role_list);
    TypedArray<CJobRoleCount> get_job_role_as_typed_array();
    void set_job_role_as_typed_array(const TypedArray<CJobRoleCount> newList);
};


class CBuildingWorld_SimpleProduction : public CBuildingWorld_SimpleJobs
{
    GDCLASS(CBuildingWorld_SimpleProduction, CBuildingWorld_SimpleJobs);

    int ticksPerCollection = 10;
    int ticksCounter       = 0;

    Ref<CResourceCountList> resourceProduce;
    Ref<CResourceCountList> resourceConsume;

    
    
protected:
    static void _bind_methods();

public:
    //bool has_spare_jobs() override;


    int get_ticks_per_collection() const;
    void set_ticks_per_collection(const int ticks_per_collection);
    
    Ref<CResourceCountList> get_resource_produce() const;
    void set_resource_produce(const Ref<CResourceCountList>& resource_produce);
    
    Ref<CResourceCountList> get_resource_consume() const;
    void set_resource_consume(const Ref<CResourceCountList>& resource_consume);



    void on_tick(float unit_ratio, float ratio) override;
    // Nothing with living here

    // Nothing iwth colonist to job

    //Override tick, manage self stats
};


class CBuildingWorld_Housing : public CBuildingWorldBase
{
    GDCLASS(CBuildingWorld_Housing, CBuildingWorldBase);

    int housingMax = 0;
    Vector<Ref<CColonist>> housedColonists;

public:
    int get_housing_max() const;
    void set_housing_max(const int housing_max);

protected:
    static void _bind_methods();

public:
    void on_tick(float unit_ratio, float ratio) override;
    // Nothing with living here

    bool has_spare_housing() override;
    bool add_colonist_to_housing(Ref<CColonist>) override;
    bool remove_colonist_from_housing(Ref<CColonist>) override;
};

class CBuildingWorld_Farm : public CBuildingWorld_SimpleJobs
{
    GDCLASS(CBuildingWorld_Farm, CBuildingWorld_SimpleJobs);

    int farmPlots = 40; // max plants

    //int maxQuality = 1; 
    
    float daysToPlant = 0.2f;
    float daysToHarvest = 0.2f;
    float dayCounter = 0.0f;
    //-- internal
    int plantedSeeds = 0; //number plants planted
    //float qualityPlants = 0; //quality on plants
    Ref<CResourceCount> foodGain = NULL;

public:
    Ref<CResourceCount> get_food_gain() const;
    void set_food_gain(const Ref<CResourceCount>& food_gain);

protected:
    static void _bind_methods();

public:
    void on_tick(float unit_ratio, float ratio) override;

    int get_farm_plots() const;
    void set_farm_plots(const int farm_plots);
    float get_ticks_to_plant() const;
    void set_ticks_to_plant(const float ticks_to_plant);
    float get_ticks_to_harvest() const;
    void set_ticks_to_harvest(const float ticks_to_harvest);
};
