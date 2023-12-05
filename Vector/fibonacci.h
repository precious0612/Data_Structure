#ifndef FIBONACCI_H
#define FIBONACCI_H

// Define the Fib class
class Fib {
private:
    int f, g;  // f = fib(k-1), g = fib(k-2)

public:
    // Initialize the Fibonacci sequence to have the specified number
    Fib(int n) {
        f = 1;
        g = 0;
        while (g < n) {
            next();
        }
    }

    // Move to the next Fibonacci number
    void next() {
        g += f;
        f = g - f;
    }

    // Move to the previous Fibonacci number
    void prev() {
        f = g - f;
        g -= f;
    }

    // Get the current Fibonacci number
    int get() const { return g; }
};

#endif // FIBONACCI_H
