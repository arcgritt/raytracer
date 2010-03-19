#ifndef VECTOR_H
#define VECTOR_H

class Vector
{
public:
    Vector();
    Vector(float, float, float);
    Vector(float, float, float, float);
    void printDebug();
    void normalise();
    float Length();
    float SquareLength();
    float dot(const Vector&);
    void operator+=(const Vector&);
    Vector operator+(const Vector&);
    Vector operator-();
    void operator-=(const Vector&);
    Vector operator-(const Vector&);
    Vector operator*(float _m);
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
