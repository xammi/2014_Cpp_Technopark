#ifndef NETPROCESSOR_H
#define NETPROCESSOR_H

#include "NeuNetUI.h"
#include "Tester.h"
#include "../DataProcess/ImageStorage.h"
#include "../DataProcess/ImageProcessor.h"
#include "../NetTutors/BackPropTutor.h"
#include "../Factory/backpropfactory.h"

namespace NetManagers {

    using DataProcess::AbstractStorage;
    using DataProcess::ImageStorage;
    using DataProcess::AbstractProcessor;
    using DataProcess::ImageProcessor;

    using NetTutors::AbstractTutor;
    using NetTutors::BackPropTutor;

//-------------------------------------------------------------------------------------------------
class NetProcessor : public QObject {

    Q_OBJECT

private slots:
    void onLoadNet();
    void onCreateNet();
    void onCreateTopology();

    void onAddData();
    void onRemoveData();
    void onFormDataSet();

    void onTestNetSingle();
    void onTestNetDataSet();

    void onTeachNet();
    void onSaveNet();
    void onRemoveNet();

public:
    static const NetProcessor & get_self();

protected:
    NetProcessor();
    ~NetProcessor();

    void setDefaultConf();
    void connectUI();

private:
    NeuNetUI *gui;
    Tester *tester;
    AbstractTutor *tutor;

    AbstractStorage *dataStore;
    AbstractProcessor *dataProc;
};
//-------------------------------------------------------------------------------------------------
} // namespace NetManagers
#endif // NETPROCESSOR_H
