#ifndef ENTITYDATAFACTORY_H
#define ENTITYDATAFACTORY_H

#include <memory>
#include <string>
#include "EntityData.h"

/**
 * Factory class of EntityData and its subclasses.
 *
 * Factory class that instanciates and returns EntityData and its subclasses.
 */
class EntityDataFactory
{
  public:
    static EntityDataFactory& GetInstance();
    // We don't want factory instance to be copied
    EntityDataFactory(EntityDataFactory const&) = delete;
    void operator=(EntityDataFactory const&) = delete;
    std::shared_ptr<EntityData> CreateData(const CsvType type, const std::string &data);
  private:
    EntityDataFactory() {};
};

#endif
