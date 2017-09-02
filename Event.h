#pragma once
#include <vector>
#include <functional>

struct Event {

    std::vector<std::function<void(int)>> callbacks;

    void listen(std::function<void(int)> callback) {
        callbacks.push_back(callback);
    }

    void trigger(int value) {
        for each (std::function<void(int)> callback in callbacks){
            callback(value);
        }
    }
};

struct Box{
    int value;
    Event changed;

    Box(int value) {
        this->value = value;
    }

    int get() {
        return this->value;
    }

    void set(int newvalue) {
        if (value == newvalue) {
            return;
        }
        this->value = newvalue;
        changed.trigger(newvalue);
    }
};