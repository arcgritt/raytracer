#ifndef FRAGMENT_H
#define FRAGMENT_H

#include "Colour.h"
#include "Material.h"
#include "Vector.h"

/// \file Fragment.h
/// \author Adam Gritt
/// \version 1.0
/// \date 2010-04-01 \n

/// Revision History : \n
/// v1.0 - Assignment submission version

/// \class Fragment
/// \brief Encapsulates the information needed for shading algorithms for a point of intersection
/// \todo

class Fragment {
    public:
        /// \brief The default constructor
        Fragment();
        
        /// \brief Constructs an object containing information relevant to colour calculations for this intersection
        /// @param[in] _position    the point of intersection
        /// @param[in] _normal      the surface normal of the intersected object
        /// @param[in] _colour      the colour of the intersected object
        /// @param[in] _material    the material of the intersected object
        Fragment(
            const Vector& _position,
            const Vector& _normal,
            const Colour& _colour,
            const Material& _material
        );
        
        /// \brief Returns the point of intersection
        /// \returns  the point of intersection
        Vector GetPosition() const {
            return c_position;
        }
        
        /// \brief Returns the surface normal of the intersected object
        /// \returns the surface normal of the intersected object
        Vector GetNormal() const {
            return c_normal;
        }
        
        /// \brief Returns the colour of the intersected object
        /// \returns the colour of the intersected object
        Colour GetColour() const {
            return c_colour;
        }
        
        /// \brief Returns the material of the intersected object
        /// \returns the material of the intersected object
        Material GetMaterial() const {
            return c_material;
        }
        
    private:
        /// Point of intersection
        Vector c_position;
        
        /// Surface normal of the intersected object
        Vector c_normal;
        
        /// Colour of the intersected object
        Colour c_colour;
        
        /// Material of the intersected object
        Material c_material;
};

#endif // FRAGMENT_H
