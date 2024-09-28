#include "MultiMapIterator.h"
#include "MultiMap.h"


MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
    currentElem = col.head;
    currentValueIndex = 0;
}

TElem MultiMapIterator::getCurrent() const{
    if (!valid()) {
        throw exception();
    }
    return std::make_pair(currentElem->key, currentElem->values[currentValueIndex]);
}

bool MultiMapIterator::valid() const {
    return currentElem != nullptr && currentValueIndex < currentElem->values.size();
}

void MultiMapIterator::next() {
    if (!valid()) {
        throw exception();
    }
    currentValueIndex++;
    if (currentValueIndex >= currentElem->values.size()) {
        currentElem = currentElem->next;
        currentValueIndex = 0;
    }
    
}

void MultiMapIterator::first() {
    currentElem = col.head;
    currentValueIndex = 0;
}
