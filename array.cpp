#include <iostream>
#include <stdexcept>
using namespace std;

template <class T>
class Array {
private:
    T* data;
    int size;
    int count;
    int grow;

public:
    Array() {
        data = nullptr;
        size = 0;
        count = 0;
        grow = 1;
    }

    ~Array() {
        delete[] data;
    }

    int GetSize() {
        return size;
    }

    void SetSize(int newSize, int newGrow = 1) {
        if (newSize < 0)
            return;

        if (newGrow > 0)
            grow = newGrow;

        if (newSize == size)
            return;

        T* newData = nullptr;

        if (newSize > 0) {
            newData = new T[newSize];

            int elementsToCopy = (count < newSize) ? count : newSize;

            for (int i = 0; i < elementsToCopy; i++)
                newData[i] = data[i];
        }

        delete[] data;
        data = newData;
        size = newSize;

        if (count > size)
            count = size;
    }

    int GetUpperBound() {
        return count - 1;
    }

    bool IsEmpty() {
        return count == 0;
    }

    void FreeExtra() {
        SetSize(count, grow);
    }

    void RemoveAll() {
        delete[] data;
        data = nullptr;
        size = 0;
        count = 0;
    }

    T GetAt(int index) {
        if (index < 0 || index >= count)
            throw out_of_range("Invalid index");

        return data[index];
    }

    void SetAt(int index, T value) {
        if (index < 0 || index >= size)
            throw out_of_range("Invalid index");

        data[index] = value;

        if (index >= count)
            count = index + 1;
    }

    T& operator[](int index) {
        if (index < 0 || index >= count)
            throw out_of_range("Invalid index");

        return data[index];
    }

    void Add(T value) {
        if (count >= size)
            SetSize(size + grow, grow);

        data[count] = value;
        count++;
    }

    void Append(Array<T>& other) {
        for (int i = 0; i < other.count; i++)
            Add(other.data[i]);
    }

    Array<T>& operator=(const Array<T>& other) {
        if (this == &other)
            return *this;

        delete[] data;

        size = other.size;
        count = other.count;
        grow = other.grow;

        data = nullptr;

        if (size > 0) {
            data = new T[size];

            for (int i = 0; i < count; i++)
                data[i] = other.data[i];
        }

        return *this;
    }

    T* GetData() {
        return data;
    }

    void InsertAt(int index, T value, int number = 1) {
        if (index < 0 || index > count || number < 0)
            throw out_of_range("Invalid index");

        if (number == 0)
            return;

        while (count + number > size)
            SetSize(size + grow, grow);

        for (int i = count - 1; i >= index; i--)
            data[i + number] = data[i];

        for (int i = 0; i < number; i++)
            data[index + i] = value;

        count += number;
    }

    void RemoveAt(int index, int number = 1) {
        if (index < 0 || number < 0 || index + number > count)
            throw out_of_range("Invalid index");

        if (number == 0)
            return;

        for (int i = index; i < count - number; i++)
            data[i] = data[i + number];

        count -= number;
    }
};

int main() {
    Array<int> arr;

    arr.SetSize(5, 5);

    arr.Add(10);
    arr.Add(20);
    arr.Add(30);

    


    return 0;







}
