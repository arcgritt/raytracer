#ifndef RENDERABLEOBJECT_H
#define RENDERABLEOBJECT_H

#include "Colour.h"
#include "Fragment.h"
#include "Material.h"
#include "Vector.h"

/// \file RenderableObject.h
/// \author Adam Gritt
/// \version 1.0
/// \date 2010-04-01 \n

/// Revision History : \n
/// v1.0 - Assignment submission version

/// \class RenderableObject
/// \brief Abstract class which encapsulates the data belonging to an object which can be rendered
/// \todo

class RenderableObject {
    public:
        /// \brief The default constructor
        RenderableObject();
        
        /// \brief Returns the position of this object
        /// \returns the position of this object
        Vector GetPosition() const {
            return m_position;
        }
        
        /// \brief Returns the colour of this object
        /// \returns the colour of this object
        Colour GetColour() const {
            return m_colour;
        }
        
        /// \brief Returns the material of this object
        /// \returns the material of this object
        Material GetMaterial() const {
            return m_material;
        }
        
        /// \brief Checks if the input ray intersects with this object
        /// @param[in] _rayOrigin   the origin of the ray to perform the intersection test with
        /// @param[in] _ray         the direction of the ray to perform the intersection test with
        /// \returns -1 if no intersection occured, or the square distance from _rayOrigin to the point of intersection
        virtual float DoIntersection(
            Vector& _rayOrigin,
            Vector& _ray
        ) =0;
        
        /// \brief Retrieves a fragment containing the information necessary to shade this object
        /// @param[in] _rayOrigin   the point of origin of the ray
        /// @param[in] _ray         the direction of the ray
        /// @param[in] _distance    the distance between the ray's origin and the point of intersection (saves calculating it again)
        /// \returns a fragment containing the information necessary to shade this object
        virtual Fragment GetFragment(
            Vector& _rayOrigin,
            Vector& _ray,
            const float _distance
        ) =0;
    private:
        /// Position of the object
        Vector m_position;
        
        /// Colour of the object
        Colour m_colour;
        
        /// Material of the object
        Material m_material;
    protected:
        /// \brief Sets the position of this object
        /// @param[in] _the position of this object
        void SetPosition(const Vector& _position) {
            m_position = _position;
        }
        
        /// \brief Sets the colour of this object
        /// @param[in] _colour      the colour to set this object to
        void SetColour(const Colour& _colour) {
            m_colour = _colour;
        }
        
        /// \brief Sets the material of this object
        /// @param[in] _material    the material to set this object to
        void SetMaterial(const Material& _material) {
            m_material = _material;
        }
};

#endif // RENDERABLEOBJECT_H
