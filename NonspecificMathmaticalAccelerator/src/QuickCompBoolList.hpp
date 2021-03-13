#include "Arduino.h"

template <size_t MaxLen>
class QuickCompBoolList{
private:
    size_t position = 0;
    uint32_t comp = 0;

public:
    uint32_t data = 0;
    QuickCompBoolList();
    void push(const bool &value);
    bool isAllTrue();
    bool isAllFalse();
};
