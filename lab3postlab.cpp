#include <iostream>
#include <stdexcept>
#include <cmath>
#include <algorithm>

using namespace std;

class Double_vector {

private:
    double* internal_array;
    int array_size;
    int array_capacity;


public:
    // Constructors
    Double_vector() : internal_array(nullptr), array_size(0), array_capacity(0) {}

    Double_vector(int n, double val = 0.0) : internal_array(nullptr), array_size(n), array_capacity(n) {
        if (n > 0) {
            internal_array = new double[n];
            for (int i = 0; i < n; ++i) {
                internal_array[i] = val;
            }
        }
    }

    Double_vector(const Double_vector& x) : internal_array(nullptr), array_size(x.array_size), array_capacity(x.array_capacity) {
        if (array_size > 0) {
            internal_array = new double[array_size];
            for (int i = 0; i < array_size; ++i) {
                internal_array[i] = x.internal_array[i];
            }
        }
    }

    ~Double_vector() {
        delete[] internal_array;
    }

    // Assignment operator
    Double_vector& operator=(const Double_vector& x) {
        if (this != &x) {
            delete[] internal_array;
            array_size = x.array_size;
            array_capacity = x.array_capacity;
            internal_array = new double[array_capacity];
            for (int i = 0; i < array_size; ++i) {
                internal_array[i] = x.internal_array[i];
            }
        }
        return *this;
    }

    // Capacity
    int size() const { return array_size; }

    int max_size() const { return array_capacity; }

    void resize(int n, double val = 0.0) {
        if (n < 0) {
            throw out_of_range("Negative size");
        }

        if (n > array_capacity) {
            reserve(n);
        }

        if (n > array_size) {
            for (int i = array_size; i < n; ++i) {
                internal_array[i] = val;
            }
        }

        array_size = n;
    }

    int capacity() const { return array_capacity; }

    bool empty() const { return array_size == 0; }

    void reserve(int n) {
        if (n > array_capacity) {
            double* temp = new double[n];
            for (int i = 0; i < array_size; ++i) {
                temp[i] = internal_array[i];
            }
            delete[] internal_array;
            internal_array = temp;
            array_capacity = n;
        }
    }

    void shrink_to_fit() {
        if (array_capacity > array_size) {
            array_capacity = array_size;
            double* temp = new double[array_capacity];
            for (int i = 0; i < array_size; ++i) {
                temp[i] = internal_array[i];
            }
            delete[] internal_array;
            internal_array = temp;
        }
    }

    // Element access
    double& operator[](int pos) {
        return internal_array[pos];
    }

    const double& operator[](int pos) const {
        return internal_array[pos];
    }

    double& at(int pos) {
        if (pos < 0 || pos >= array_size) {
            throw std::out_of_range("Out of range");
        }
        return internal_array[pos];
    }

    const double& at(int pos) const {
        if (pos < 0 || pos >= array_size) {
            throw std::out_of_range("Out of range");
        }
        return internal_array[pos];
    }

    double& front() {
        return internal_array[0];
    }

    const double& front() const {
        return internal_array[0];
    }

    double& back() {
        return internal_array[array_size - 1];
    }

    const double& back() const {
        return internal_array[array_size - 1];
    }

    double* data() {
        return internal_array;
    }

    const double* data() const {
        return internal_array;
    }

    // Modifiers
    void push_back(double value) {
        if (array_size == array_capacity) {
            reserve(array_capacity == 0 ? 1 : 2 * array_capacity);
        }
        internal_array[array_size++] = value;
    }

    void pop_back() {
        if (array_size > 0) {
            --array_size;
        }
    }

    void insert(int pos, double value) {
        if (pos < 0 || pos > array_size) {
            throw std::out_of_range("Invalid position for insertion");
        }

        if (array_size == array_capacity) {
            reserve(array_capacity == 0 ? 1 : 2 * array_capacity);
        }

        for (int i = array_size; i > pos; --i) {
            internal_array[i] = internal_array[i - 1];
        }

        internal_array[pos] = value;
        ++array_size;
    }

    void erase(int pos) {
        if (pos < 0 || pos >= array_size) {
            throw std::out_of_range("Invalid position for erasing");
        }

        for (int i = pos; i < array_size - 1; ++i) {
            internal_array[i] = internal_array[i + 1];
        }

        --array_size;
    }

    void clear() {
        array_size = 0;
    }


};

// Friend function for ostream
std::ostream& operator<<(std::ostream& os, const Double_vector& vec) {
    os << "[ ";
    for (int i = 0; i < vec.size(); ++i) {
        os << vec[i] << " ";
    }
    os << "]";
    return os;
}

void addData(Double_vector& dataVector) {
    cout << "Enter numeric data (separate values by spaces): ";
    double value;
    while (cin >> value) {
        dataVector.push_back(value);
        // Check if the user pressed enter without providing input
        if (cin.peek() == '\n') {
            break;
        }
    }
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Data added successfully.\n";
}

void calculateMean(const Double_vector& dataVector) {
    double sum = 0.0;
    for (int i = 0; i < dataVector.size(); ++i) {
        sum += dataVector[i];
    }
    double mean = sum / dataVector.size();
    std::cout << "Mean: " << mean << "\n";
}

void calculateMedian(const Double_vector& dataVector) {
    Double_vector temp(dataVector);
    sort(temp.data(), temp.data() + temp.size());
    double median;
    if (temp.size() % 2 == 0) {
        median = (temp[temp.size() / 2 - 1] + temp[temp.size() / 2]) / 2.0;
    } else {
        median = temp[temp.size() / 2];
    }
    std::cout << "Median: " << median << "\n";
}

void calculateStandardDeviation(const Double_vector& dataVector) {
    double mean = 0.0;
    for (int i = 0; i < dataVector.size(); ++i) {
        mean += dataVector[i];
    }
    mean /= dataVector.size();

    double variance = 0.0;
    for (int i = 0; i < dataVector.size(); ++i) {
        variance += (dataVector[i] - mean) * (dataVector[i] - mean);
    }
    variance /= dataVector.size();

    double standardDeviation = std::sqrt(variance);
    std::cout << "Standard Deviation: " << standardDeviation << "\n";
}

void displayData(const Double_vector& dataVector) {
    std::cout << "Current Data: ";
    for (int i = 0; i < dataVector.size(); ++i) {
        std::cout << dataVector[i] << " ";
    }
    std::cout << "\n";
}

void showMenu() {
    std::cout << "=== Statistics Calculator ===\n"
              << "1. Add Data\n"
              << "2. Calculate Mean\n"
              << "3. Calculate Median\n"
              << "4. Calculate Standard Deviation\n"
              << "5. Display Data\n"
              << "6. Exit\n"
              << "Enter your choice: ";
}

void runStatisticsCalculator() {
    Double_vector dataVector;
    int choice;
    do {
        showMenu();
        std::cin >> choice;
        switch (choice) {
            case 1:
                addData(dataVector);
                break;
            case 2:
                calculateMean(dataVector);
                break;
            case 3:
                calculateMedian(dataVector);
                break;
            case 4:
                calculateStandardDeviation(dataVector);
                break;
            case 5:
                displayData(dataVector);
                break;
            case 6:
                std::cout << "Exiting the program. Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 6);
}

int main() {
    runStatisticsCalculator();
    return 0;
}