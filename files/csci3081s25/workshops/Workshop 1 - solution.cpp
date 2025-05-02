#include <iostream>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For seeding random numbers

int main() {
    // Seed random number generator
    srand(time(0));

    int numQuestions, score = 0;

    std::cout << "Welcome to the Math Quiz Generator!\n";
    std::cout << "How many questions would you like to answer? ";
    std::cin >> numQuestions;

    for (int i = 0; i < numQuestions; ++i) {
        int a = rand() % 10 + 1;  // Random number between 1 and 10
        int b = rand() % 10 + 1;
        int operation = rand() % 3;  // 0 = +, 1 = -, 2 = *
        int correctAnswer;

        std::cout << "Question " << (i + 1) << ": ";
        if (operation == 0) {
            std::cout << a << " + " << b << " = ? ";
            correctAnswer = a + b;
        } else if (operation == 1) {
            std::cout << a << " - " << b << " = ? ";
            correctAnswer = a - b;
        } else {
            std::cout << a << " * " << b << " = ? ";
            correctAnswer = a * b;
        }

        int userAnswer;
        std::cin >> userAnswer;

        if (userAnswer == correctAnswer) {
            std::cout << "Correct!\n";
            ++score;
        } else {
            std::cout << "Incorrect. The correct answer was " << correctAnswer << ".\n";
        }
    }

    std::cout << "You answered " << score << " out of " << numQuestions << " questions correctly.\n";
    return 0;
}
