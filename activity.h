#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <QString>

class Activity
{

public:
    enum TYPE
    {
        SPORTS = 1,
        AFTER_SCHOOL
    };

public:
    Activity();
    Activity(const QString &id, const QString &code, const QString &name,
             const QString &description, const QString &advisor, const QString &limit);

    QString id() const;
    void setId(const QString &id);

    QString code() const;
    void setCode(const QString &code);

    QString name() const;
    void setName(const QString &name);

    QString description() const;
    void setDescription(const QString &description);

    QString advisor() const;
    void setAdvisor(const QString &advisor);

    QString limit() const;
    void setLimit(const QString &limit);

    int getType() const;
    void setType(const TYPE type);
    void setType(const int type);

private:
    QString mId;
    QString mCode;
    int mType;
    QString mName;
    QString mDescription;
    QString mAdvisor;
    QString mLimit;
};

#endif // ACTIVITY_H
