#pragma once
#include <math.h>
#include <functional>

template <typename T, int size>
struct Vector
{
    T &x;
    T &y;
    T &z;
    T vals[size] = {};

    Vector() : x(vals[0]), y(vals[1]), z(vals[2])
    {
    }

    Vector(T x, T y) : x(vals[0]), y(vals[1]), z(vals[2])
    {
        vals[0] = x;
        vals[1] = y;
    }

    Vector(T x, T y, T z) : x(vals[0]), y(vals[1]), z(vals[2])
    {
        vals[0] = x;
        vals[1] = y;
        vals[2] = z;
    }

    Vector(const Vector &other) : x(vals[0]), y(vals[1]), z(vals[2])
    {
        memcpy(vals, other.vals, sizeof vals);
    }

    Vector &operator=(Vector &other)
    {
        memcpy(vals, other.vals, sizeof vals);
        return *this;
    }

    Vector &add(const Vector &other)
    {
        for (int i = 0; i < size; i++)
        {
            vals[i] += other.vals[i];
        }
        return *this;
    }

    Vector &sub(const Vector &other)
    {
        for (int i = 0; i < size; i++)
        {
            vals[i] -= other.vals[i];
        }
        return *this;
    }

    Vector &scale(float scalar)
    {
        for (int i = 0; i < size; i++)
        {
            vals[i] *= scalar;
        }
        return *this;
    }

    T dot(const Vector &other) const
    {
        T sum = 0;
        for (int i = 0; i < size; i++)
        {
            sum += vals[i] * other.vals[i];
        }
        return sum;
    }

    Vector cross(const Vector &other)
    {
        return Vector(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x);
    }

    Vector &normalise()
    {
        return scale(1 / length());
    }

    float length()
    {
        float sum = 0;
        for (int i = 0; i < size; i++)
        {
            sum += vals[i] * vals[i];
        }
        return pow(sum, 0.5);
    }

    Vector lerp(const Vector &other, float weight)
    {
        return c().add(other.c().sub(*this).scale(weight));
    }

    Vector c() const
    {
        return *this;
    }

    T &operator[](int index)
    {
        return vals[index];
    }

    Vector &rotX(float t)
    {
        float cost = cosf(t);
        float sint = sinf(t);
        T xp = x;
        T yp = y * cost - z * sint;
        T zp = y * sint + z * cost;
        x = xp;
        y = yp;
        z = zp;
        return *this;
    }

    Vector &rotY(float t)
    {
        float cost = cosf(t);
        float sint = sinf(t);
        T xp = x * cost + z * sint;
        T yp = y;
        T zp = -x * sint + z * cost;
        x = xp;
        y = yp;
        z = zp;
        return *this;
    }

    Vector &rotZ(float t)
    {
        float cost = cosf(t);
        float sint = sinf(t);
        T xp = x * cost - y * sint;
        T yp = x * sint + y * cost;
        T zp = z;
        x = xp;
        y = yp;
        z = zp;
        return *this;
    }

    Vector<int, size> round()
    {
        Vector<int, size> v;
        for (int i = 0; i < size; i++)
        {
            v[i] = std::round(vals[i]);
        }
        return v;
    }

    template <int newsize>
    Vector<T, newsize> resize()
    {
        Vector<T, newsize> v;
        for (int i = 0; i < newsize; i++)
        {
            v[i] = vals[i];
        }
        return v;
    }
    
    void loop(std::function<void(Vector)> callback) {
		Vector scratch;
		callback(scratch);
		while (!scratch.incr(*this)) {
			callback(scratch);
		}
	}

	bool incr(Vector& base) {
		int carry = 0;
		vals[size - 1]++;

		for (int i = size - 1; i >= 0; i--) {
			int result = vals[i] + carry;

			if (result >= base[i]) {
				vals[i] = 0;
				carry = 1;
			} else {
				vals[i] = result;
				carry = 0;
				return false;
			}
		}
		return true;
	}
};

typedef Vector<int, 2> V2i;
typedef Vector<float, 2> V2f;
typedef Vector<int, 3> V3i;
typedef Vector<float, 3> V3f;
