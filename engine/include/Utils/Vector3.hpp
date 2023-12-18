/*
** Malek PROJECT, 2023
** GAME ENGINE
** File description:
** Vector3
*/

#ifndef GAME_ENGINE_VECTOR3_HPP
#define GAME_ENGINE_VECTOR3_HPP

namespace Engine
{

    template <typename T>

    class Vector3
    {
    public:
        // ------------------------------------------- Constructors -------------------------------------------

        /**
         * @brief Construct a new Vector3 object without parameters
         */
        Vector3()
        {
            _x = 0;
            _y = 0;
            _z = 0;
        };

        /**
         * @brief Construct a new Vector3 object with parameters
         *
         * @param x
         * @param y
         * @param z
         */
        Vector3(T x, T y, T z)
        {
            _x = x;
            _y = y;
            _z = z;
        };

        /**
         * @brief Construct a new Vector3 object with a Vector3
         *
         * @param src
         */
        Vector3(const Vector3 &src)
        {
            _x = src._x;
            _y = src._y;
            _z = src._z;
        }

        // ------------------------------------------- Destructor -------------------------------------------

        /**
         * @brief Destroy the Vector3 object
         */
        ~Vector3() = default;

        // ------------------------------------------- Operators -------------------------------------------

        /**
         * @brief Operator = of Vector3
         *
         * @param src
         * @return Vector3&
         */
        inline Vector3 &operator=(const Vector3 &src)
        {
            _x = src._x;
            _y = src._y;
            _z = src._z;
            return *this;
        }

        /**
         * @brief Operator + of Vector3
         *
         * @param src
         * @return Vector3
         */
        inline Vector3 operator+(const Vector3 &src)
        {
            return Vector3(_x + src._x, _y + src._y, _z + src._z);
        }

        /**
         * @brief Operator - of Vector3
         *
         * @param src
         * @return Vector3
         */
        inline Vector3 operator-(const Vector3 &src)
        {
            return Vector3(_x - src._x, _y - src._y, _z - src._z);
        }

        /**
         * @brief Operator * of Vector3
         *
         * @param src
         * @return Vector3
         */
        inline Vector3 operator*(const Vector3 &src)
        {
            return Vector3(_x * src._x, _y * src._y, _z * src._z);
        }

        /**
         * @brief Operator / of Vector3
         *
         * @param src
         * @return Vector3
         */
        inline Vector3 operator/(const Vector3 &src)
        {
            return Vector3(_x / src._x, _y / src._y, _z / src._z);
        }

        /**
         * @brief Operator += of Vector3
         *
         * @param src
         * @return Vector3&
         */
        inline Vector3 &operator+=(const Vector3 &src)
        {
            _x += src._x;
            _y += src._y;
            _z += src._z;
            return *this;
        }

        /**
         * @brief Operator -= of Vector3
         *
         * @param src
         * @return Vector3&
         */
        inline Vector3 &operator-=(const Vector3 &src)
        {
            _x -= src._x;
            _y -= src._y;
            _z -= src._z;
            return *this;
        }

        /**
         * @brief Operator *= of Vector3
         *
         * @param src
         * @return Vector3&
         */
        inline Vector3 &operator*=(const Vector3 &src)
        {
            _x *= src._x;
            _y *= src._y;
            _z *= src._z;
            return *this;
        }

        /**
         * @brief Operator /= of Vector3
         *
         * @param src
         * @return Vector3&
         */
        inline Vector3 &operator/=(const Vector3 &src)
        {
            _x /= src._x;
            _y /= src._y;
            _z /= src._z;
            return *this;
        }

        /**
         * @brief Operator == of Vector3
         *
         * @param src
         * @return true
         * @return false
         */
        inline bool operator==(const Vector3 &src)
        {
            return (_x == src._x && _y == src._y && _z == src._z);
        }

        /**
         * @brief Operator != of Vector3
         *
         * @param src
         * @return true
         * @return false
         */
        inline bool operator!=(const Vector3 &src)
        {
            return (_x != src._x || _y != src._y || _z != src._z);
        }

        // ------------------------------------------- Getters -------------------------------------------

        /**
         * @brief Get the X object
         *
         * @return T
         */
        inline T GetX(void) const
        {
            return _x;
        }

        /**
         * @brief Get the Y object
         *
         * @return T
         */
        inline T GetY(void) const
        {
            return _y;
        }

        /**
         * @brief Get the Z object
         *
         * @return T
         */
        inline T GetZ(void) const
        {
            return _z;
        }

        // ------------------------------------------- Setters -------------------------------------------

        /**
         * @brief Set the X object
         *
         * @param x
         */
        inline void SetX(T x)
        {
            _x = x;
        }

        /**
         * @brief Set the Y object
         *
         * @param y
         */
        inline void SetY(T y)
        {
            _y = y;
        }

        /**
         * @brief Set the Z object
         *
         * @param z
         */
        inline void SetZ(T z)
        {
            _z = z;
        }

        /**
         * @brief Set the X, Y and Z object
         *
         * @param x
         * @param y
         * @param z
         */
        inline void Set(T x, T y, T z)
        {
            _x = x;
            _y = y;
            _z = z;
        }

        /**
         * @brief Set the X, Y and Z object
         *
         * @param src
         */
        inline void Set(const Vector3 &src)
        {
            _x = src._x;
            _y = src._y;
            _z = src._z;
        }

        /**
         * @brief Set the X, Y and Z object to zero
         *
         * @param src
         */
        inline void SetZero(void)
        {
            _x = 0;
            _y = 0;
            _z = 0;
        }

        /**
         * @brief Set the X, Y and Z object to one
         *
         * @param src
         */
        inline void SetOne(void)
        {
            _x = 1;
            _y = 1;
            _z = 1;
        }

        // ------------------------------------------- Methods -------------------------------------------

        /**
         * @brief check if the X, Y and Z object are zero
         *
         * @param src
         */
        inline bool IsZero(void) const
        {
            return (_x == 0 && _y == 0 && _z == 0);
        }

        /**
         * @brief check if the X, Y and Z object are one
         *
         * @param src
         */
        inline bool IsOne(void) const
        {
            return (_x == 1 && _y == 1 && _z == 1);
        }

        /**
         * @brief Rotate the vector around the X axis
         *
         * @param angle
         * @return Vector3
         */
        inline Vector3 Rotate(const Vector3 &src, T angle) const
        {
            T s = std::sin(angle);
            T c = std::cos(angle);
            return Vector3(_x * (src._x * src._x * (1 - c) + c) + _y * (src._x * src._y * (1 - c) - src._z * s) +
                               _z * (src._x * src._z * (1 - c) + src._y * s),
                           _x * (src._y * src._x * (1 - c) + src._z * s) + _y * (src._y * src._y * (1 - c) + c) +
                               _z * (src._y * src._z * (1 - c) - src._x * s),
                           _x * (src._z * src._x * (1 - c) - src._y * s) +
                               _y * (src._z * src._y * (1 - c) + src._x * s) + _z * (src._z * src._z * (1 - c) + c));
        }

        /**
         * @brief Rotate the vector around the X axis
         *
         * @param angle
         * @return Vector3
         */
        inline Vector3 RotateAround(const Vector3 &src, const Vector3 &point, T angle) const
        {
            return Vector3(_x - point._x, _y - point._y, _z - point._z).Rotate(src, angle) +
                   Vector3(point._x, point._y, point._z);
        }


        /**
         * @brief Get the angle between two vectors
         *
         * @param src
         * @return T
         */
        inline Vector3 Scale(const Vector3 &src) const
        {
            return Vector3(_x * src._x, _y * src._y, _z * src._z);
        }

    private:
        // ------------------------------------------- Attributes -------------------------------------------
        T _x;
        T _y;
        T _z;
    };
}

#endif // GAME_ENGINE_VECTOR3_HPP