#ifndef CINDBVIEW_H 
#define CINDBVIEW_H 

#include <QObject>
#include "CinArtifactSet.h"
#include "CinParamSet.h"

class CinDatabase;

//! A class that manages a view of a cinema database 
/*!
 *  This class manages an interface to a Cinema Database,
 *  which is a set of parameters and a set of artifacts
 *  There can be many different interfaces to the database,
 *  which is why this class contains the parameters and
 *  artifacts, but only points to the database 
*/
class CinDBView : public QObject
{
    Q_OBJECT

    public:
        // constructor
        CinDBView() {}

        void setDatabase(CinDatabase *db);
        int load(const QString &db, const QString &table);
        void updateArtifacts();

    private:
        void getArtifactQueryString(QString &query);
        bool getFullPathToArtifact(const QString &artifact, QString &fullpath);

        CinArtifactSet mArtifacts;
        CinParamSet    mParams;
        CinDatabase   *mDatabase;

    public:
        CinArtifactSet *getArtifacts()  {return &mArtifacts;}
        CinParamSet    *getParameters() {return &mParams;}
        CinDatabase    *getDatabase()   {return mDatabase;}

    signals:

};

#endif // CINDBVIEW_H