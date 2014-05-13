#ifndef PTRVECTOR_H
#define PTRVECTOR_H

#include <QVector>

//-------------------------------------------------------------------------------------------------
template <typename Value>
class PtrVector : public QVector<Value *>
{
public:
    PtrVector() {}

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

    void remove(int i) {
        Value * tmp_ptr = this->operator [](i);
        if (tmp_ptr)
            delete tmp_ptr;

        QVector<Value *>::remove(i);
    }

    void remove(int i, int n) {
        for (int cnt = 0; cnt < n; ++cnt) {
            Value *tmp_ptr = this->operator [](i + cnt);
            if (tmp_ptr)
                delete tmp_ptr;
        }

        QVector<Value *>::remove(i, n);
    }
};

//-------------------------------------------------------------------------------------------------

#endif // PTRVECTOR_H
