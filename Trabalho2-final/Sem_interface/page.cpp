#include "page.h"

// Construtor
Page::Page(int value) : value(value) {}

// Retorna valor da página
int Page::getValue() const {
    return value;
}