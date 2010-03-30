/// \file Colour.h
/// \brief encapsulates an RGBA colour object
/// \author Adam Gritt

#ifndef COLOUR_H
#define COLOUR_H

#include <string>

class Colour
{
public:
    /// \brief default constructor
    Colour();

    /// \brief
    /// @param[in] _r   red, from 0.0f to 1.0f if you want to use GetColour256
    /// @param[in] _g   green, as above
    /// @param[in] _b   blue, as above
    Colour(float _r, float _g, float _b);

    /// \brief
    /// @param[in] _r   red, from 0.0f to 1.0f if you want to use GetColour256
    /// @param[in] _g   green, as above
    /// @param[in] _b   blue, as above
    /// @param[in] _a   alpha, as above
    Colour(float _r, float _g, float _b, float _a);

    /// \brief
    /// @param[in] _colour  float[4] to return colour information in
    void GetColour(float* _colour);

    void Floor();

    void Ceil();

    /// \brief
    /// @param[in] _colour  unsigned int[4] to return colour information in
    void GetColour256(unsigned int* _colour);

    //void operator+(Colour& _colour);

    Colour operator+(Colour& _colour);

    /// \brief Adds this colour and the input colour
    /// @param[in] _colour  colour to be added
    void operator+=(Colour& _colour);

    /// \brief Multiplies this colour and the input colour
    /// @param[in] _colour  colour to be multiplied
    void operator*=(Colour& _colour);


    /// \brief Multiplies this colour by a float value
    /// @param[in] _multiplier  amount to multiply this colour by
    void operator*=(float _multiplier);


    void operator/=(float _multiplier);

    /// \brief Determines the average of two colours. Input order is irrelevant
    /// @param[in] _colour1 the first colour
    /// @param[in] _colour2 the second colour
    static Colour Average(Colour& _colour1, Colour& _colour2);

    /// \brief Averages this colour with the input colour. Equivalent to _colour&=(this)
    /// @param[in] _colour the colour to average this colour with
    void operator&=(Colour& _colour);

    /// \brief Returns a string containing debug information about this object
    std::string GetDebugInformation();

private:
    float m_r;
    float m_g;
    float m_b;
    float m_a;
};

#endif // COLOUR_H
