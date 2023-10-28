// Note that there is no need for "using namespace std",
// since no C++ standard libraries are used.

double addition(double left, double right) {
    return left + right;
}


double subtraction(double left, double right) {
    return left - right;
}


double multiplication(double left, double right) {
    return left * right;
}


double division(double left, double right) {
    return left / right;
}

double exponentiation(double left, double right) {
    int i = 1;
    double multiplier = left;
    while ( i < right) {
        left *= multiplier;
        ++i;
    }
    return left;
}
