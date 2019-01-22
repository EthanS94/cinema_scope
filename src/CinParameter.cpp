#include "CinParameter.h"
#include "CinCore.h"
#include <QString>
#include <QDebug>

const char *CinParameter::TypeNames[] = {"UNDEFINED", "STRING", "FLOAT", "INT"};
const float CinParameter::NO_VALUE = -0.0001010101;
const float CinParameter::NO_PREV  = -0.0002020202;
const float CinParameter::NO_NEXT  = -0.0003030303;
const float CinParameter::NOT_SET  = -0.0004040404;

/*! \brief Convenience function to print names instead of ints
 *
 */
const char *CinParameter::GetNameForType(CinParameter::Type type)
{
    return TypeNames[type];
}

CinParameter::CinParameter(const QString &name, CinParameter::Type type)
{
    mName     = name;
    mType     = type;
    mMin      = CinParameter::NOT_SET; 
    mMax      = CinParameter::NOT_SET;
    mCurValue = CinParameter::NOT_SET; 
    mCurID    = 0;
}

/*! \brief Add unique values to the datastructure
 *
 */
void CinParameter::recordValue(float value)
{
    if (not (std::find(mValues.begin(), mValues.end(), value) != mValues.end()))
    {
        mValues.push_back(value);
    }
}

/*! \brief Do internal data sync after all values added 
 *
 */
void CinParameter::finalizeValues()
{
    if (mValues.size() != 0) 
    {
        std::sort(mValues.begin(), mValues.end());

        // make sure min and max are still correct
        setMin(mValues.front());
        setMax(mValues.back());
    }
}

void CinParameter::print()
{
    qDebug() << "PARAMETER: " << mName << mValues;
}


bool CinParameter::valueExists(float value)
{
    return (std::find(mValues.begin(), mValues.end(), value) != mValues.end());
}


int  CinParameter::getNumValues() 
{ 
    return mValues.size();
}

bool CinParameter::valueAsString(QString &value, int id)
{
    bool result = false;
    float fValue = 0.0;

    result = valueAt(fValue, id);
    value = "";
    if (result)
    {
        value = QString::number(fValue);
    }

    return result;
}

bool CinParameter::setToValueAt(int valueID)
{
    bool result = false;
    float fValue;

    result = valueAt(fValue, valueID);
    if (result)
    {
        // current ID is set by this call
        setValue(fValue);

    } else {
        // TODO report error
    }

    return result;
}

// TODO error checking
bool CinParameter::setValue(float value)
{
    bool result = valueExists(value); 

    if (result)
    {
        mCurValue = value;
        mCurID = getIDForValue(mCurValue);

            // this needs to be changed, when the redesign to QString
            // is complete.
        emit valueChanged(QString::number(getValue()), getCurID()); 
    }

    return result;
}

bool CinParameter::isValidID(int valueID)
{
    return ((valueID >= 0) && (static_cast<unsigned int>(valueID) < mValues.size()));
}

bool CinParameter::valueAt(float &value, int valueID)
{
    bool result = false;

    value = CinParameter::NO_VALUE;
    result = isValidID(valueID);
    if (result)
    {
        value = mValues.at(valueID);
    } else {
        qDebug() << "ERROR: invalid ID passed to CinParameter: " << valueID;
    }

    return result;
}

int CinParameter::getIDForValue(float value)
{
    std::vector<float>::iterator it = std::find(mValues.begin(), mValues.end(), value);
    if (it != mValues.end())
    {
        return std::distance(mValues.begin() , it);
    } else {
        qDebug() << "ERROR value not found";
        return CinCore::NOTFOUND; 
    } 
}

/*! \brief Set this parameter to the prev value 
 *
 *  If the value is at the beginning, wrap to the end 
 */
void CinParameter::incrementValue()
{
    if (getCurID() == getLastID())
    {
        // wrap to beginning
        setToValueAt(0);
    } else {
        setToValueAt( getCurID() + 1 );
    }
}

/*! \brief Set this parameter to the next value 
 *
 *  If the value is at the end, wrap to beginning
 */
void CinParameter::decrementValue()
{
    if (getCurID() == 0)
    {
        // wrap to end
        setToValueAt(getLastID());
    } else {
        setToValueAt( getCurID() - 1 );
    }
}
