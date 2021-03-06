#ifndef ABSTRACTPROCESSOR_H
#define ABSTRACTPROCESSOR_H

#include "../includes.h"

namespace DataProcess {

//-------------------------------------------------------------------------------------------------
class InputData
{
public:
    InputData() {}

    //
    InputData(QString &textData) {
        this->values.resize(textData.length());
        for(int i = 0; i < textData.length(); ++i) {
            this->values[i] = 1.0 * (int)(textData[i].toLatin1());
        }
    }

    bool operator == (const InputData &rhs) { return values==rhs.values; }

public:
    QVector <double> values;
};
typedef QVector<InputData *> InputDataSet;

class OutputData
{
public:
    OutputData() {}
    OutputData(int size) { values.resize(size); }    

    void swapVecs(OutputData &from) {
        this->values.clear();
        this->values.resize(from.values.size());
        this->values = from.values;
    }

    void clearAndFill() { this->values.resize(1); this->values.fill(1); }

    bool operator == (const OutputData &rhs) { return values == rhs.values; }

public:
    QVector <double> values;
};
typedef QVector<OutputData *> OutputDataSet;

//-------------------------------------------------------------------------------------------------
struct InOutData {
    InputData in;
    OutputData out;
};

template <class Item>
void deleteAll(QVector<Item *> & vector) {
    for (Item * item : vector)
        if (item)
            delete item;
}

//-------------------------------------------------------------------------------------------------
struct AbstractProcessor : public QObject {
    virtual ~AbstractProcessor() {}

    virtual void processTxt(InputData & input, const QString & str) {
        for (QChar ch : str) {
            if (ch == '0')
                input.values.append(0);
            else if (ch == '1')
                input.values.append(1);
        }
    }

    virtual void processData(InputData &, const QImage &) = 0;
};
//-------------------------------------------------------------------------------------------------
} // namespace DataProcess

#endif // ABSTRACTPROCESSOR_H
