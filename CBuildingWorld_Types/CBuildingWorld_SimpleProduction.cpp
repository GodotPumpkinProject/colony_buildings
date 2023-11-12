#include "colony_buildings/CBuildingServer.h"
#include "colony_buildings/CBuildingWorldBase.h"
#include "colony_resources/ResourceServer.h"

int CBuildingWorld_SimpleProduction::get_ticks_per_collection() const
{
    return ticksPerCollection;
}

void CBuildingWorld_SimpleProduction::set_ticks_per_collection(const int ticks_per_collection)
{
    ticksPerCollection = ticks_per_collection;
}

Ref<CResourceCountList> CBuildingWorld_SimpleProduction::get_resource_produce() const
{
    return resourceProduce;
}

void CBuildingWorld_SimpleProduction::set_resource_produce(const Ref<CResourceCountList>& resource_produce)
{
    resourceProduce = resource_produce;
}

Ref<CResourceCountList> CBuildingWorld_SimpleProduction::get_resource_consume() const
{
    return resourceConsume;
}

void CBuildingWorld_SimpleProduction::set_resource_consume(const Ref<CResourceCountList>& resource_consume)
{
    resourceConsume = resource_consume;
}


void CBuildingWorld_SimpleProduction::_bind_methods()
{

    ClassDB::bind_method(D_METHOD("set_resource_consume", "resources_consumed"), &CBuildingWorld_SimpleProduction::set_resource_consume);
    ClassDB::bind_method(D_METHOD("get_resource_consume"), &CBuildingWorld_SimpleProduction::get_resource_consume);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "resources_consumed", PROPERTY_HINT_RESOURCE_TYPE, ("CResourceCountList")), "set_resource_consume", "get_resource_consume");
    
    ClassDB::bind_method(D_METHOD("set_resource_produce", "resources_produced"), &CBuildingWorld_SimpleProduction::set_resource_produce);
    ClassDB::bind_method(D_METHOD("get_resource_produce"), &CBuildingWorld_SimpleProduction::get_resource_produce);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "resources_produced", PROPERTY_HINT_RESOURCE_TYPE, ("CResourceCountList")), "set_resource_produce", "get_resource_produce");
    
    ClassDB::bind_method(D_METHOD("set_ticks_per_collection", "ticks_per_produce"), &CBuildingWorld_SimpleProduction::set_ticks_per_collection);
    ClassDB::bind_method(D_METHOD("get_ticks_per_collection"), &CBuildingWorld_SimpleProduction::get_ticks_per_collection);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "ticks_per_produce"), "set_ticks_per_collection", "get_ticks_per_collection");
}


void CBuildingWorld_SimpleProduction::on_tick(float unit_ratio, float ratio)
{
    CBuildingWorldBase::on_tick(unit_ratio, ratio);
    
    if (ticksPerCollection <= 0){ return; }
    this->ticksCounter += 1;
    while(this->ticksCounter > this->ticksPerCollection)
    {
        this->ticksCounter -=  this->ticksPerCollection;
        //resourceConsume
        auto colonyResourceServer =ColonyResourceServer::get_singleton();
        if (!colonyResourceServer){break;}
        if (!colonyResourceServer->HasResourceQuantity(this->resourceConsume)){break;}
        ColonyResourceServer::get_singleton()->RemoveResourceList(this->resourceConsume);
        ColonyResourceServer::get_singleton()->AddResourceList(this->resourceProduce);
    }
}
