#include "CinArtifactSet.h"
#include "CinParamSet.h"

#include <QObject>
#include <QString>
#include <QMap>
#include <QDebug>

const QString CinArtifactSet::NOTFOUND = "CinArtifactSetNOTFOUND";

CinArtifactSet::CinArtifactSet()
{
}

void CinArtifactSet::set(const QString &key, const QString &value) 
{
    mArtifacts.insert(key, value); 
}

bool CinArtifactSet::contains(const QString &key)
{
    return mArtifacts.contains(key);
}

const QString &CinArtifactSet::get(const QString &key)
{
    QMap<QString, QString>::iterator found = mArtifacts.find(key);
    if (found != mArtifacts.end())
    {
        qDebug() << "FOUND: " << found.value();
        return found.value();
    }

    return CinArtifactSet::NOTFOUND; 
}

void CinArtifactSet::init(CinDatabase &db)
{
    const QStringList &cols = db.getArtifactColumnNames();
    for (int i=0;i<cols.count();i++)
    {
        set(cols.at(i), "InitialValue"); 
    }
}
