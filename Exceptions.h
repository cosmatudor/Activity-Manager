#pragma once

#include <string>
#include <exception>
#include <utility>

using namespace std;

class RepositoryExcepetion {
private:
    string message;
public:
    explicit RepositoryExcepetion(string message) : message(std::move(message)) {};

    friend ostream &operator<<(ostream &out, const RepositoryExcepetion &excepetion);
};


class ValidationException {
private:
    string message;
public:
    explicit ValidationException(string message) : message(std::move(message)) {}

    const string& getMessage() const;
};


class UIException {
private:
    string message;
public:
    explicit UIException(string message) : message(std::move(message)) {}

    const string& getMessage() const;
};