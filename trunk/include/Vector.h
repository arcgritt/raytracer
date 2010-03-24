#ifndef VECTOR_H
#define VECTOR_H

#include <string>

class Vector
{
public:
    Vector();

    Vector(float _x, float _y, float _z);

    Vector(float _x, float _y, float _z, float _w);

    void Normalise();

    float Length();

    float SquareLength();

    void operator+=(const Vector& _v);

    Vector operator+(const Vector& _v);

    Vector operator-();

    void operator-=(const Vector& _v);

    Vector operator-(const Vector& _v);

    Vector operator*(float _multiplier);

    static Vector Cross(const Vector& _v1, const Vector& _v2);

    static float Dot(const Vector & _v1, const Vector& _v2);

    float GetX() const { return m_x; }

    float GetY() const { return m_y; }

    float GetZ() const { return m_z; }

    /// \brief Returns a string containing debug information about this object
    std::string GetDebugInformation();
private:
    union
    {
        #pragma pack(push,1)
        struct
        {
            /// x component of the vector
            float m_x;
            /// y component of the vector
            float m_y;
            /// z component of the vector
            float m_z;
            /// w component of the vector 0= Vector 1=Point
            float m_w;
        };
        #pragma pack(pop)
        /// \brief array of four floats mapped to the x,y,z,w components of the vector useful for openGL fv data types
        /// this is mapped as a union to the following \n
        /// m_x == m_openGL[0] \n
        /// m_y == m_openGL[1] \n
        /// m_z == m_openGL[2] \n
        /// m_w == m_openGL[3] \n

        float m_vector[4];
    };
};

#endif // VECTOR_H
