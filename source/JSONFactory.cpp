//
// Created by vesko on 16.06.22.
//

#include "../headers/JSONFactory.h"

const JSONBaseCreator* JSONFactory::getCreator(const char c) const
{
    for (int i = 0; i < count; ++i)
    {
        if (strchr(creators[i]->getKeyChars(), c) != nullptr)
        {
            return creators[i];
        }
    }

    return nullptr;
}

JSONFactory& JSONFactory::getFactory()
{
    static JSONFactory theFactory;
    return theFactory;
}

void JSONFactory::registerJSONBase(const JSONBaseCreator *creator)
{
    creators[count++] = creator;
}

JSONBase* JSONFactory::createJSONBase(std::istream &in)
{
    char c;
    in >> c;

    const JSONBaseCreator* creator = getCreator(c);

    if (creator)
    {
        in.seekg(-1, std::ios_base::cur);
        return creator->createJSONBase(in);
    }

    return nullptr;
}
