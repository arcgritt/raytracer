#ifndef COLOUR_H
#define COLOUR_H

#include <string>

/// \file Colour.h
/// \author Adam Gritt
/// \version 1.0
/// \date 2010-04-01 \n

/// Revision History : \n
/// v1.0 - Assignment submission version

/// \class Colour
/// \brief encapsulates an RGBA colour object
/// \todo static function which takes an array of colours and averages them


class Colour
{
public:
    /// \brief The default constructor
    Colour();

    /// \brief Constructs a Colour with the specifed RGB values (from 0.0f to 1.0f) and 1.0f alpha
    /// @param[in] _r   red, from 0.0f to 1.0f if you want to use GetColour256
    /// @param[in] _g   green, as above
    /// @param[in] _b   blue, as above
    Colour(const float _r, const float _g, const float _b);

    /// \brief Constructs a Colour with the specified RGBA values (from 0.0f to 1.0f)
    /// @param[in] _r   red, from 0.0f to 1.0f if you want to use GetColour256
    /// @param[in] _g   green, as above
    /// @param[in] _b   blue, as above
    /// @param[in] _a   alpha, as above
    Colour(const float _r, const float _g, const float _b, const float _a);

    /// \brief Fills the input array with this colour's information
    /// @param[in] _colour  float[4] to return colour information in
    void GetColour(float* _colour);

    /// \brief Floors the colour's attributes to a minimum of 0.0f;
    void Floor();

    /// \brief Ceils the colour's attributes to a maximum of 1.0f;
    void Ceil();

    /// \brief Fills the input array with this colour's information in 8-bit integer format (0-255)
    /// @param[in] _colour  unsigned int[4] to return colour information in
    void GetColour256(unsigned int* _colour);

    /// \brief Adds this coluor and the input colour as a new object and returns it
    /// @param[in] _colour the colour to add to this one
    /// \returns a new colour equal to the sum of this colour plus the input colour
    Colour operator+(const Colour& _colour);

    /// \brief Adds this colour and the input colour
    /// @param[in] _colour  colour to be added
    void operator+=(const Colour& _colour);

    /// \brief Multiplies this colour and the input colour
    /// @param[in] _colour  colour to be multiplied
    void operator*=(const Colour& _colour);

    /// \brief Multiplies this colour by a float value
    /// @param[in] _multiplier  amount to multiply this colour by
    void operator*=(const float _multiplier);

    /// \brief Divides this colour by a float value
    /// @param[in] _multiplier the amount fo divide this colour by
    void operator/=(const float _multiplier);

    /// \brief Determines the average of two colours. Input order is irrelevant
    /// @param[in] _colour1 the first colour
    /// @param[in] _colour2 the second colour
    static Colour Average(const Colour& _colour1, const Colour& _colour2);

    /// \brief Averages this colour with the input colour. Equivalent to _colour&=(this)
    /// @param[in] _colour the colour to average this colour with
    void operator&=(const Colour& _colour);

    /// \brief Retrieves debug information about this object
    /// \returns A string containing debug information about this object, formatted on one line
    std::string GetDebugInformation();

private:
    /// Red component of the colour
    float m_r;

    /// Green component of the colour
    float m_g;

    /// Blue component of the colour
    float m_b;

    /// Alpha component of the colour
    float m_a;
};

#endif // COLOUR_H
