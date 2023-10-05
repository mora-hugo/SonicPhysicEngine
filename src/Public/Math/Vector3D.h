#pragma once
#include <string>
#include <utility>
#include <glm/glm.hpp>
class Vector3D
{
public:
    
    Vector3D(const double X = 0, const double Y = 0, const double Z = 0, const double W = 0);

    Vector3D(const glm::vec3 & vec3);
    /*
     *
     * Math functions
     *
     */

    
    /**
    * \brief Vector addition.
    * 
    * This function takes a constant 3D vector 'Vector' as input and returns
    * the result of adding this vector to another 3D vector.
    * 
    * \param Vector The 3D vector to be added.
    * \return A new 3D vector resulting from the addition.
    */
    Vector3D Add(const Vector3D & Vector) const;

    /**
     * \brief Vector subtraction.
     * 
     * This function takes a constant 3D vector 'Vector' as input and returns
     * the result of subtracting it from another 3D vector.
     * 
     * \param Vector The 3D vector to be subtracted.
     * \return A new 3D vector resulting from the subtraction.
     */
    Vector3D Sub(const Vector3D & Vector) const;

    /**
     * \brief Calculate the magnitude (length) of the vector.
     * 
     * This function computes and returns the magnitude (length) of the vector.
     * 
     * \return The magnitude of the vector.
     */
    double Magnitude() const;

    /**
     * \brief Calculate the squared magnitude of the vector.
     * 
     * This function computes and returns the squared magnitude of the vector.
     * 
     * \return The squared magnitude of the vector.
     */
    double MagnitudeSquared() const;

    /**
     * \brief Scalar multiplication.
     * 
     * This function takes a scalar value 'Scalar' as input and returns
     * a new 3D vector resulting from multiplying the current vector by the scalar.
     * 
     * \param Scalar The scalar value to multiply with.
     * \return A new 3D vector resulting from the scalar multiplication.
     */
    Vector3D Multiply(const double Scalar) const;


    /**
     * Divide each component of the vector by a scalar.
     *
     * @param Scalar The scalar by which to divide the components of the vector.
     * @return A new vector where each component is the result of dividing the
     *         corresponding component of the current vector by the scalar.
     */
    Vector3D Divide(const double Scalar) const;
    

    /**
     * Negate the components of the vector by changing their sign.
     *
     * @return A new vector where each component is the negation of the corresponding
     *         component of the current vector.
     */
    Vector3D Negate() const;
    

    /**
     * \brief Normalize the vector.
     * 
     * This function normalizes the vector to a unit vector and scales it by the given scalar value.
     * 
     * \param Scalar The scalar value to scale the normalized vector.
     * \return A new 3D vector representing the normalized and scaled vector.
     */
    Vector3D Normalize() const;
    
    /**
     * \brief Component-wise product of two vectors.
     *
     * This function computes and returns the component-wise product (Hadamard product) of
     * the current vector with another 3D vector 'Vector'. Each component of the resulting
     * vector is obtained by multiplying the corresponding components of the two input vectors.
     *
     * \param Vector The other 3D vector for the component-wise product.
     * \return A new 3D vector representing the component-wise product.
     */
    Vector3D ComponentProduct(const Vector3D& Vector) const;

    /**
     * \brief Calculate the dot product (scalar product) with another vector.
     *
     * This function calculates and returns the dot product (scalar product) of the current
     * vector with another 3D vector 'Vector'. The dot product is a scalar value obtained
     * by summing the products of the corresponding components of the two vectors.
     *
     * \param Vector The other 3D vector for the dot product.
     * \return The dot product of the two vectors.
     */
    double DotProduct(const Vector3D& Vector) const;

    /**
     * \brief Calculate the cross product (vector product) with another vector.
     *
     * This function calculates and returns the cross product (vector product) of the current
     * vector with another 3D vector 'Vector'. The cross product produces a new 3D vector
     * that is orthogonal to both input vectors and has a magnitude equal to the area of the
     * parallelogram formed by the two vectors.
     *
     * \param Vector The other 3D vector for the cross product.
     * \return A new 3D vector representing the cross product.
     */
    Vector3D CrossProduct(const Vector3D& Vector) const;


    static Vector3D Zero();

    
 
    /**
     * \brief Convert to a glm::vec2.
     * 
     * This method converts the current 3D vector to a glm::vec2.
     * 
     * \return A glm::vec2 representation of the vector (X, Y components).
     */
    inline glm::vec2 toVec2() const { return glm::vec2(X, Y); }

    /**
     * \brief Convert to a glm::vec3.
     * 
     * This method converts the current 3D vector to a glm::vec3.
     * 
     * \return A glm::vec3 representation of the vector (X, Y, Z components).
     */
    inline glm::vec3 toVec3() const  { return glm::vec3(X, Y, Z); }
    
    Vector3D operator+(const Vector3D& Vector) const {
        return (this->Add(Vector));
    }

  
    operator glm::vec3() const
    {
        return this->toVec3();
    }

    operator std::string() const
    {
     return "("+std::to_string(X)+","+std::to_string(Y)+","+std::to_string(Z)+","+std::to_string(W)+")";
    }
    
    Vector3D operator-(const Vector3D& Vector) const {
        return (this->Sub(Vector));
    }

    Vector3D operator*(const double& Scalar) const {
        return (this->Multiply(Scalar));
    }

    
    /*
     * Getters
     */
    
    inline double GetX() const
    {
        return X;
    }

    inline double GetY() const
    {
        return Y;
    }

    inline double GetZ() const
    {
        return Z;
    }

    inline double GetW() const
    {
        return W;
    }

    /*
     * Setters
     */

    inline void SetX(const double x) {this->X = x;}
    
    inline void SetY(const double y) {this->Y = y;}
    
    inline void SetZ(const double z) {this->Z = z;}

private:
    double X, Y, Z, W;
    
};
