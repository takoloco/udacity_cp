#include <memory>
#include <string>

#include "EntityDataFactory.h"
#include "EntityData.h"

EntityDataFactory& EntityDataFactory::getInstance()
{
  static EntityDataFactory instance;
  return instance;
}
