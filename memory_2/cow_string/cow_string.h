#include <cstdint>

using namespace std;

struct State
{
    int ref_count = 1;
    size_t size = 0;
    size_t capacity = 2;
    char* ptr = new char[2];

    ~State() {
        delete[] ptr;
    }
};

class CowString
{
private:
    State* data;

public:
    CowString() 
        : data(new State) 
        {}
    CowString(const CowString &other) {
        if (this != &other) {
            data = other.data;
            (data->ref_count)++;
        }
    }

    ~CowString() {
        (data->ref_count)--;
        if (data->ref_count == 0) {
            delete data;
        }
    }

    const char &At(size_t index) const {
        return data->ptr[index];
    }
    char &operator[](size_t index) {
        if (data->ref_count > 1) {
            State* NewData = new State;
            NewData->size = data->size;
            NewData->capacity = data->capacity;
            char* n = new char[NewData->capacity];
            for (size_t i = 0; i < data->size; ++i) {
                n[i] = data->ptr[i];
            }
            delete[] NewData->ptr;
            NewData->ptr = n;
            (data->ref_count)--;
            if (data->ref_count == 0) {
                delete data;
            }
            data = NewData;
        }
        return data->ptr[index];
    }
    CowString& operator=(const CowString& other) {
        if (this != &other) {
            (data->ref_count)--;
            if (data->ref_count == 0) {
                delete data;
            }
            data = other.data;
            (data->ref_count)++;
        }
        return *this;
    }
    const char &Back() const {
        return data->ptr[(int) data->size - 1];
    }

    void PushBack(char c) {
        if (data->ref_count > 1) {
            State* NewData = new State;
            NewData->size = data->size;
            NewData->capacity = data->capacity;
            char* n = new char[NewData->capacity];
            for (size_t i = 0; i < data->size; ++i) {
                n[i] = data->ptr[i];
            }
            delete[] NewData->ptr;
            NewData->ptr = n;
            (data->ref_count)--;
            if (data->ref_count == 0) {
                delete data;
            }
            data = NewData;
        }
        if (data->size == data->capacity) {
            char* n = new char[2 * data->capacity];
            for (size_t i = 0; i < data->size; ++i) {
                n[i] = data->ptr[i];
            }
            delete[] data->ptr;
            data->ptr = n;
            data->capacity = 2 * data->capacity;
        }
        data->ptr[data->size] = c;
        (data->size)++;
    }

    size_t Size() const {
        return data->size;
    }
    size_t Capacity() const {
        return data->capacity;
    }

    void Reserve(size_t capacity_) {
        if (capacity_ <= data->capacity) {
            return;
        }
        char* NewData = new char[capacity_];
        for (size_t i = 0; i < data->size; ++i) {
            NewData[i] = data->ptr[i];
        }
        delete[] data->ptr;
        data->ptr = NewData;
        data->capacity = capacity_;
    }
    void Resize(size_t size_) {
        if (size_ > data->capacity) {
            char* NewData = new char[size_];
            for (size_t i = 0; i < data->size; ++i) {
                NewData[i] = data->ptr[i];
            }
            delete[] data->ptr;
            data->ptr = NewData;
            data->capacity = size_;
        }
        else {
            if (size_ <= data->size) {
                char* NewData = new char[data->capacity];
                for (size_t i = 0; i < size_; ++i) {
                    NewData[i] = data->ptr[i];
                }
                delete[] data->ptr;
                data->ptr = NewData;
            }
            else {
                char *NewData = new char[data->capacity];
                for (size_t i = 0; i < data->size; ++i) {
                    NewData[i] = data->ptr[i];
                }
                for (size_t i = data->size; i < size_; ++i) {
                    NewData[i] = 0;
                }
                delete[] data->ptr;
                data->ptr = NewData;
            }
        }
        data->size = size_;
    }
};
