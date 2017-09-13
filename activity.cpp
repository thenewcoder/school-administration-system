#include "activity.h"

Activity::Activity()
    : mId(""), mCode(""), mName("")
    , mDescription(""), mAdvisor("")
    , mLimit("")
{

}

Activity::Activity(const QString &id, const QString &code, const QString &name, const QString &description,
                   const QString &advisor, const QString &limit)
    : mId(id), mCode(code), mName(name)
    , mDescription(description), mAdvisor(advisor)
    , mLimit(limit)
{

}

QString Activity::id() const
{
    return mId;
}

void Activity::setId(const QString &id)
{
    mId = id;
}

QString Activity::code() const
{
    return mCode;
}

void Activity::setCode(const QString &code)
{
    mCode = code;
}

QString Activity::name() const
{
    return mName;
}

void Activity::setName(const QString &name)
{
    mName = name;
}

QString Activity::description() const
{
    return mDescription;
}

void Activity::setDescription(const QString &description)
{
    mDescription = description;
}

QString Activity::advisor() const
{
    return mAdvisor;
}

void Activity::setAdvisor(const QString &advisor)
{
    mAdvisor = advisor;
}

QString Activity::limit() const
{
    return mLimit;
}

void Activity::setLimit(const QString &limit)
{
    mLimit = limit;
}

int Activity::getType() const
{
    return mType;
}

void Activity::setType(const TYPE type)
{
    mType = type;
}

void Activity::setType(const int type)
{
    mType = type;
}
