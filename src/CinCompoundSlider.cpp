#include "CinCompoundSlider.h"
#include "CinParameter.h"
#include <QDebug>

CinCompoundSlider::CinCompoundSlider(QWidget *parent) : QWidget(parent)
{
    mLabel.setText("unset");
    // mLabel.setFrameStyle(QFrame::Panel | QFrame::Sunken);
    mLabel.setFixedSize(50, 20);
    mLabel.setAlignment(Qt::AlignRight);

    mValue.setText("unset");
    mValue.setFrameStyle(QFrame::Panel | QFrame::Sunken);
    mValue.setFixedSize(50, 20);
    mValue.setAlignment(Qt::AlignRight);

    mSlider.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    mSlider.setMinimum(0);
    mSlider.setMaximum(10);
    mSlider.setOrientation(Qt::Horizontal);
    mSlider.setTickInterval(1);
    mSlider.setTickPosition(QSlider::TicksAbove);

    mLayout.addWidget(&mLabel);
    mLayout.addWidget(&mSlider);
    mLayout.addWidget(&mValue);
    this->setLayout(&mLayout);

    QObject::connect(&mSlider, SIGNAL(valueChanged(int)), this, SLOT(onSliderValueChanged(int)));
}

void CinCompoundSlider::onSliderValueChanged(int value)
{
    QString stringValue;

    if (getValue(stringValue, value))
    {
        mValue.setText(stringValue);
        mParameter->setValue(mParameter->valueAt(value));

        emit valueChanged(mParameter->getName(), stringValue);
    }
}

bool CinCompoundSlider::getValue(QString &value, int id)
{
    return mParameter->valueAsString(value, id); 
}

bool CinCompoundSlider::setParameter(CinParameter *p)
{
    bool result = false;

    if (p) 
    {
        mParameter = p;

        mLabel.setText(mParameter->getName());

        int numValues = mParameter->getNumValues();
        mSlider.setMinimum(0);
        mSlider.setMaximum(numValues-1);
        mSlider.setValue(mParameter->valueAt(0));

        result = true;
    } else {
        // TODO express warning
    }

    return result;
}

void CinCompoundSlider::onParameterValueChanged(float value, int valueID)
{
}