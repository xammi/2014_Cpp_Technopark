#ifndef PTRVECTOR_H
#define PTRVECTOR_H

#include <QVector>
#include <type_traits>

struct Containable {
};

typedef int Index;
typedef const Index CIndex;

//-------------------------------------------------------------------------------------------------
template <typename Value>
class PtrVector : public QVector<Value *>
{
public:
    PtrVector() {
        static_assert(std::is_base_of <Containable, Value>::value,
                      "PtrVector value_type must inherit Containable");
    }

    ~PtrVector() {
        this->clear();
    }

    void clear() {
        for (int I = 0; I < this->size(); ++I)
            if (this->operator [](I)) {
                delete (this->operator [](I));
            }

        QVector<Value *>::clear();
    }
};

//-------------------------------------------------------------------------------------------------

#endif // PTRVECTOR_H
