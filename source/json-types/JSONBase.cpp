//
// Created by vesko on 12.06.22.
//

#include "../../headers/json-types/JSONBase.h"
#include "../../headers/JSONFactory.h"
#include "../../headers/JSONExceptions.h"

void JSONBase::search(const std::string &key, std::vector<JSONBase*> &jsonArray) const
{}

void JSONBase::edit(std::vector<std::string> &elements, JSONBase *value, size_t level)
{
    throw ElementNotFound(elements[level]);
}

void JSONBase::create(std::vector<std::string> &elements, JSONBase *value, size_t level)
{
    if (elements.size() - 1 == level)
    {
        throw CannotCreateElement(elements[level]);
    }
    throw ElementAlreadyExists(elements[level]);
}

void JSONBase::remove(std::vector<std::string> &elements, size_t level, bool toDelete)
{
    throw ElementNotFound(elements[level]);
}

const JSONBase* const JSONBase::findElement(std::vector<std::string> &elements, size_t level) const
{
    return nullptr;
}

JSONBaseCreator::JSONBaseCreator(const char *keyChars) : keyChars(keyChars)
{
    JSONFactory::getFactory().registerJSONBase(this);
}

const char *JSONBaseCreator::getKeyChars() const
{
    return keyChars;
}
