//
// Created by vesko on 12.06.22.
//

#include "../../headers/json-types/JSONBase.h"
#include "../../headers/JSONFactory.h"

JSONBaseCreator::JSONBaseCreator(const char *keyChars) : keyChars(keyChars)
{
    JSONFactory::getFactory().registerJSONBase(this);
}

const char *JSONBaseCreator::getKeyChars() const
{
    return keyChars;
}
