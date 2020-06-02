#include <memory>
#include <string>

#include "EntityDataFactory.h"

/**
 * Creates an instance of EntityData and returns it.
 * 
 * Creates a shared pointer to an instance of EntityData and returns it. 
 *
 * @return instance Shared pointer to a newly created instance of EntityData.
 */
std::shared_ptr<EntityData> EntityDataFactory::CreateData(
const CsvType type, const std::string &data)
{
  return std::make_shared<EntityData>(type, data);
};

/**
 * Returns instance of EntityDataFactory.
 * 
 * Returns the singleton instance of EntityDataFactory if available. If not
 * creates an instance and returns it. 
 *
 * @return instance Singleton instance of EntityDataFactory.
 */
EntityDataFactory& EntityDataFactory::getInstance()
{
  static EntityDataFactory instance;
  return instance;
}
