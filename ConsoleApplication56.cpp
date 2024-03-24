//Завдання 1
#include <iostream>
#include <string>
using namespace std;

class Animal
{
protected:
    string name;
public:
    Animal(const string& name_) : name{ name_ } {}

    virtual void makeSound() const = 0;
};

class Dog : public Animal
{
public:
    Dog(const string& name_) : Animal(name_) {}

    void makeSound() const override {
        cout << "Dog " << name << ", says: Woof! Woof!" << endl;
    }
};

class Cat : public Animal
{
public:
    Cat(const string& name_) : Animal(name_) {}

    void makeSound() const override {
        cout << "Cat " << name << ", says: Meow! Meow!" << endl;
    }
};

class Parrot : public Animal
{
public:
    Parrot(const string& name_) : Animal(name_) {}

    void makeSound() const override {
        cout << "Parrot " << name << "says: Squawk! Squawk!" << endl;
    }
};

int main()
{
    Dog dog("Bella");
    Cat cat("Myrka");
    Parrot parrot("Jonibi");

    dog.makeSound();
    cat.makeSound();
    parrot.makeSound();
}

//Завдання 2
#include <iostream>
#include <cstring>
using namespace std;

class String {
protected:
    char* str;
    int length;

public:
    String() : str(nullptr), length(0) {}

    String(const char* c_string) {
        length = strlen(c_string);
        str = new char[length + 1];
        strcpy_s(str, length + 1, c_string);
    }

    String(const String& other) : length(other.length) {
        str = new char[length + 1];
        strcpy_s(str, length + 1, other.str);
    }

    String& operator=(const String& other) {
        if (this != &other) {
            delete[] str;
            length = other.length;
            str = new char[length + 1];
            strcpy_s(str, length + 1, other.str);
        }
        return *this;
    }

    ~String() {
        delete[] str;
    }

    int getLength() const {
        return length;
    }

    void clear() {
        delete[] str;
        str = nullptr;
        length = 0;
    }

    String operator+(const String& other) const {
        String result;
        result.length = length + other.length;
        result.str = new char[result.length + 1];
        strcpy_s(result.str, result.length + 1, str);
        strcat_s(result.str, result.length + 1, other.str);
        return result;
    }

    String& operator+=(const String& other) {
        char* temp = new char[length + other.length + 1];
        strcpy_s(temp, length + other.length + 1, str);
        strcat_s(temp, length + other.length + 1, other.str);
        delete[] str;
        str = temp;
        length += other.length;
        return *this;
    }

    bool operator==(const String& other) const {
        return (length == other.length) && (strcmp(str, other.str) == 0);
    }

    bool operator!=(const String& other) const {
        return !(*this == other);
    }

    friend ostream& operator<<(ostream& os, const String& string) {
        os << string.str;
        return os;
    }
};

class BitString : public String {
public:
    BitString() : String() {}

    BitString(const char* c_string) : String() {
        bool valid = true;
        int len = strlen(c_string);
        for (int i = 0; i < len; ++i) {
            if (c_string[i] != '0' && c_string[i] != '1') {
                valid = false;
                break;
            }
        }
        if (valid) {
            length = len;
            str = new char[length + 1];
            strcpy_s(str, length + 1, c_string);
        }
    }

    BitString(const BitString& other) : String(other) {}

    BitString& operator=(const BitString& other) {
        if (this != &other) {
            String::operator=(other);
        }
        return *this;
    }

    void toggleSign() {
        for (int i = 0; i < length; ++i) {
            if (str[i] == '0') {
                str[i] = '1';
            }
            else {
                str[i] = '0';
            }
        }
    }

    BitString operator+(const BitString& other) const {
        BitString result;
        result.length = length + other.length;
        result.str = new char[result.length + 1];
        strcpy_s(result.str, result.length + 1, str);
        strcat_s(result.str, result.length + 1, other.str);
        return result;
    }

    bool operator==(const BitString& other) const {
        return String::operator==(other);
    }

    bool operator!=(const BitString& other) const {
        return String::operator!=(other);
    }
};

int main() {
    String str1("Hello");
    String str2(" World");
    String str3 = str1 + str2;
    cout << "Concatenated string: " << str3 << endl;

    BitString bitStr1("1010");
    BitString bitStr2("0110");
    BitString bitStr3 = bitStr1 + bitStr2;
    cout << "Concatenated bit string: " << bitStr3 << endl;
}