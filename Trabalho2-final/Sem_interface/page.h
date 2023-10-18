#ifndef PAGE_H
#define PAGE_H

class Page {
public:
    // Construtor
    Page(int value);
    // Retorna o valor da página
    int getValue() const;

private:
    // Valor da página
    int value;
};

#endif // PAGE_H
