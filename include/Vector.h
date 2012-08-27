#ifndef VECTOR_H
#define VECTOR_H

#include <string>

/// \file Vector.h
/// \author Adam Gritt
/// \version 1.0
/// \date 2010-04-01 \n

/// Revision History : \n
/// v1.0 - Assignment submission version

/// \class Vector
/// \brief Encapsulates a vector. Encapsulates most vector algorithms.
/// \todo

class Vector {
    public:
        /// \brief The default constructor
        Vector();
        
        /// \brief Constructs a vector with the specified x, y, z components
        /// @param[in] _x the x component of the vector
        /// @param[in] _y the y component
        /// @param[in] _z the z component
        Vector(
            const float _x,
            const float _y,
            const float _z
        );
        
        /// \brief Constructs a vector with the specified x, y, z, w components
        /// @param[in] _x the x component of the vector
        /// @param[in] _y the y component
        /// @param[in] _z the z component
        /// @param[in] _w the w component, determining whether the vector is a point or direction
        Vector(
            const float _x,
            const float _y,
            const float _z,
            const float _w
        );
        
        /// \brief Normalises the vector, setting it's length to 1
        void Normalise();
        
        /// \brief Returns the length of the vector
        /// \returns the length of the vector
        float Length();
        
        /// \brief Returns the length of the vector squared, for use when only relative distance is required, or where the output would need to be squared again later (cheaper calculation)
        /// \returns the length of the vector squared
        float SquareLength();
        
        /// \brief Adds the input vector to this vector
        /// @param[in] _v the vector to be added to this one
        void operator+=(const Vector& _v);
        
        /// \brief Returns a vector which is the sum of this vector and the input vector
        /// @param[in] _v the vector to be added to this one
        /// \returns a vector which is the sum of this vector and the input vector
        Vector operator+(const Vector& _v);
        
        /// \brief Returns a vector in which the sign of each of the components has been reversed
        /// \returns a vector in which the sign of each of the components has been reversed
        Vector operator-();
        
        /// \brief Subtracts the input vector from this vector
        /// @param[in] _v the vector to be subtracted from this one
        void operator-=(const Vector& _v);
        
        /// \brief Returns a vector which is equal to this vector minus the input vector
        /// @param[in] _v the vector to be subtracted from this one
        /// \returns a vector which is equal to this vector minus the input vector
        Vector operator-(const Vector& _v);
        
        /// \brief Returns a vector which is equal to this vector multiplied by the specified floating point value
        /// @param[in] _multiplier the value to multiply this vector by
        /// \returns a vector which is equal to this vector multiplied by by the specified floating point value
        Vector operator*(const float _multiplier);
        
        /// \brief Returns a vector which is equal to this vector divided by the specified floating point value
        /// \returns a vector which is equal to this vector divided by the specified floating point value
        Vector operator/(const float _divisor);
        
        /// \brief Returns the cross product of the two input vectors
        /// @param[in] _v1 the first vector
        /// @param[in] _v2 the second vector
        /// \returns the cross product of the two input vectors
        static Vector Cross(
            const Vector& _v1,
            const Vector& _v2
        );
        
        /// \brief Returns the dot product of the two input vectors
        /// @param[in] _v1 the first vector
        /// @param[in] _v2 the second vector
        /// \returns the dot product of the two input vectors
        static float Dot(
            const Vector& _v1,
            const Vector& _v2
        );
        
        /// \brief Returns the x component of the vector
        /// \returns the x component of the vector
        float GetX() const {
            return m_x;
        }
        
        /// \brief Returns the y component of the vector
        /// \returns the y component of the vector
        float GetY() const {
            return m_y;
        }
        
        /// \brief Returns the z component of the vector
        /// \returns the z component of the vector
        float GetZ() const {
            return m_z;
        }
        
        /// \brief Returns a string containing debug information about this object
        /// \returns a string containing debug information about this object
        const std::string GetDebugInformation();
    private:
        union {
#pragma pack(push,1)
            struct {
                /// X component of the vector
                float m_x;
                /// Y component of the vector
                float m_y;
                /// Z component of the vector
                float m_z;
                /// W component of the vector 0= Vector 1=Point
                float m_w;
            };
#pragma pack(pop)
            
            float m_vector[4];
        };
};

#endif // VECTOR_H
