//
// Created by vesko on 12.06.22.
//

#ifndef JSON_PARSER_JSONBASE_H
#define JSON_PARSER_JSONBASE_H


#include <string>
#include <vector>
#include <istream>
#include <cstring>

class JSONBase
{
public:
    virtual ~JSONBase() = default;
    virtual JSONBase* clone() const = 0;

public:
    virtual void output(std::ostream &out, size_t level, bool isCompact) const = 0;
    virtual void search(const std::string& key, std::vector<JSONBase*> &jsonArray) const;
    virtual void edit(std::vector<std::string> &elements, JSONBase* value, size_t level);
    virtual void create(std::vector<std::string> &elements, JSONBase* value, size_t level);
    virtual void remove(std::vector<std::string> &elements, size_t level, bool toDelete);
    virtual const JSONBase* const findElement(std::vector<std::string> &elements, size_t level) const;

    class Iterator
    {
        friend class JSONBase;

    public:
        virtual Iterator* operator++() = 0;
        virtual Iterator* operator++(int) = 0;

        virtual bool operator == (const Iterator* &other) const = 0;
        virtual bool operator != (const Iterator* &other) const = 0;

        virtual JSONBase* operator*() const = 0;
        virtual JSONBase* operator*() = 0;

    protected:
        Iterator(JSONBase* data) : ptr(data) {}

    protected:
        JSONBase* ptr;
    };

    virtual Iterator* begin()
    {
        throw std::invalid_argument("ne");
    }

    virtual Iterator* end()
    {
        throw std::invalid_argument("ne");
    }
};

class JSONBaseCreator
{
private:
    const char* const keyChars;

public:
    explicit JSONBaseCreator(const char* keyChars);
    virtual ~JSONBaseCreator() = default;
    JSONBaseCreator(const JSONBaseCreator&) = delete;
    JSONBaseCreator& operator=(const JSONBaseCreator&) = delete;

public:
    const char* getKeyChars() const;
    virtual JSONBase* createJSONBase(std::istream &in) const = 0;
};


#endif //JSON_PARSER_JSONBASE_H
