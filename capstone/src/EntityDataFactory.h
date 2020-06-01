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
    static EntityDataFactory& getInstance();
    // We don't want factory instance to be copied
    EntityDataFactory(EntityDataFactory const&) = delete;
    void operator=(EntityDataFactory const&) = delete;
    template <class T>
    std::shared_ptr<T> CreateData(const std::string &data)
    { return std::make_shared<T>(data); };
  private:
    EntityDataFactory() {};
};

#endif
