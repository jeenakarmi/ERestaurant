#ifndef WELCOME_H
#define WELCOME_H

#include <iostream>
#include "Customer.h"

void welcome(Customer customer) {
    std::cout << "Hello, " << customer.getUsername() << "! Place an order here.\n";
}

#endif // WELCOME_H
