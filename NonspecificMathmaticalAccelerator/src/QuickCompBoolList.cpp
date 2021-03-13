#include "QuickCompBoolList.hpp"

template <size_t MaxLen>
QuickCompBoolList<MaxLen>::QuickCompBoolList()
{ //create a int with the number of 1's expected by isAllTrue
    for (size_t i = 0; i < MaxLen; i++)
    {
        comp = comp | (1UL << i);
    }
}

template <size_t MaxLen>
void QuickCompBoolList<MaxLen>::push(const bool &value)
{
    if (position >= MaxLen)
    {
        position = 0;
    }
    data ^= (-value ^ data) & (1UL << position);
    position++;
}

template <size_t MaxLen>
bool QuickCompBoolList<MaxLen>::isAllTrue() { return data == comp; }
template <size_t MaxLen>
bool QuickCompBoolList<MaxLen>::isAllFalse() { return data == 0UL; }
