#include <memory>
#include <string>

#include "EntityDataFactory.h"
#include "EntityData.h"

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
