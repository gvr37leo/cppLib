#pragma once
#include <functional>
#include <vector>

template<class T, int n>
struct Vec {
    std::vector<T> val;

    Vec() = default;

    Vec(std::vector<T> val) : val{ val } {

    }

    Vec& operator+(Vec& rhs) {
        return c().add(rhs);
    }

    Vec& operator+=(Vec& rhs) {
        return add(rhs);
    }

    Vec& add(Vec& v) {
        iterate([&](int i) {val[i] += v.val[i]; });
        return *this;
    }

    Vec& sub(Vec& v) {
        iterate([&](int i) {val[i] -= v.val[i]; });
        return *this;
    }

    Vec& scale(float& s) {
        iterate([&](int i) {val[i] *= s; });
        return *this;
    }

    Vec& normalize() {
        return scale(1 / length())
    }

    float length() {
        T sum = 0;
        iterate([&](int i) {sum += val[i] * val[i]; });
        return (float)pow(sum, 0.5);
    }

    Vec& lerp(Vec& v, float weight) {
        return c().add(v.c().sub(*this).scale(weight));
    }

    T dot(Vec& v) {
        T sum = 0;
        iterate([&](int i) {sum += get(i) * v.get(i); });
        return sum;
    }

    T& get(int i) {
        return val[i];
    }

    void set(int i, T val) {
        val[i] = val;
    }

    T& x() {
        return val[0];
    }

    T& y() {
        return val[1];
    }

    T& z() {
        return val[2];
    }

    Vec c() {
        return Vec<T, n>(val);
    }

    bool operator ==(Vec& rhs) {
        for (int i = 0; i < n; i++) {
            if (rhs[i] != val[i]) {
                return false;
            }
        }
        return true;
    }

    T& operator[] (int i) {
        return val[i];
    }

    void iterate(std::function<void(int)> callback) {
        for (int i = 0; i < n; i++) {
            callback(i);
        }
    }

    //void loop(std::function<void(Vec&)> callback) {
    //  int counters[n];
    //  callback(counters)
    //  var i = 0;
    //  outerLoop:
    //  while (true) {
    //      while (counters[i] == this.get(i)) {
    //          counters[i] = 0;
    //          i++;
    //          if (i == counters.length) break outerLoop;
    //      }
    //      counters[i]++;
    //      callback(counters)
    //          i = 0;
    //  }
    //}
};

typedef Vec<int, 2> V2i;
typedef Vec<float, 2> V2f;
typedef Vec<int, 3> V3i;
typedef Vec<float, 3> V3f;