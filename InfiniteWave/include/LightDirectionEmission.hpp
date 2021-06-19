#pragma once

#include "Utils.hpp"
#include "LightShape.hpp"

namespace ltbl 
{

//////////////////////////////////////////////////////////////////////////
/// \brief Light with a direction (usually sun/moon)
//////////////////////////////////////////////////////////////////////////
class LightDirectionEmission : public priv::BaseLight
{
	public:
		//////////////////////////////////////////////////////////////////////////
		/// \brief Default constructor
		//////////////////////////////////////////////////////////////////////////
		LightDirectionEmission();

		//////////////////////////////////////////////////////////////////////////
		/// \brief Set the color of the light
		/// \param color The new color
		//////////////////////////////////////////////////////////////////////////
		void setColor(const sf::Color& color);

		//////////////////////////////////////////////////////////////////////////
		/// \brief Get the color of the light
		/// \return The current color
		//////////////////////////////////////////////////////////////////////////
		const sf::Color& getColor() const;

		//////////////////////////////////////////////////////////////////////////
		/// \brief Render the light
		/// \param view The current view
		/// \param lightTempTexture The light render texture
		/// \param antumbraTempTexture The antumbra render texture
		/// \param unshadowShader The unshadow shader
		/// \param shapes The shapes affected by the light
		/// \param shadowExtension The shadow extension
		//////////////////////////////////////////////////////////////////////////
		void render(const sf::View& view, sf::RenderTexture& lightTempTexture, sf::RenderTexture& antumbraTempTexture, sf::Shader& unshadowShader, const std::vector<priv::QuadtreeOccupant*>& shapes, float shadowExtension);

		//////////////////////////////////////////////////////////////////////////
		/// \brief Set the cast direction of the light
		/// Changing the cast direction will change the cast angle too
		/// \param castDirection New cast direction (the direction will be normalized)
		//////////////////////////////////////////////////////////////////////////
		void setCastDirection(const sf::Vector2f& castDirection);

		//////////////////////////////////////////////////////////////////////////
		/// \brief Get the cast direction of the light
		/// \return The current cast direction (normalized)
		//////////////////////////////////////////////////////////////////////////
		const sf::Vector2f& getCastDirection() const;

		//////////////////////////////////////////////////////////////////////////
		/// \brief Set the cast angle of the light
		/// Changing the cast angle will change the cast direction too
		/// \param angle The new angle
		//////////////////////////////////////////////////////////////////////////
		void setCastAngle(float angle);

		//////////////////////////////////////////////////////////////////////////
		/// \brief Get the cast angle of the light
		/// \return The current angle
		//////////////////////////////////////////////////////////////////////////
		float getCastAngle() const;

		//////////////////////////////////////////////////////////////////////////
		/// \brief Set the source radius
		/// \param radius The new source radius
		//////////////////////////////////////////////////////////////////////////
		void setSourceRadius(float radius);

		//////////////////////////////////////////////////////////////////////////
		/// \brief Get the source radius
		/// \return The current source radius
		//////////////////////////////////////////////////////////////////////////
		float getSourceRadius() const;

		//////////////////////////////////////////////////////////////////////////
		/// \brief Set the source distance
		/// \param distance The new source distance
		//////////////////////////////////////////////////////////////////////////
		void setSourceDistance(float distance);

		//////////////////////////////////////////////////////////////////////////
		/// \brief Get the source distance
		/// \return The current source distance
		//////////////////////////////////////////////////////////////////////////
		float getSourceDistance() const;

	private:
		//////////////////////////////////////////////////////////////////////////
		/// \brief Get the penumbras from a direction
		/// \param penumbras The penumbras
		/// \param innerBoundaryIndices The inner boundary indices
		/// \param innerBoundaryVectors The inner boundary vectors
		/// \param outerBoundaryIndices The outer boundary indices
		/// \param outerBoundaryVectors The outer boundary vectors
		/// \param shape The shape
		//////////////////////////////////////////////////////////////////////////
		void getPenumbrasDirection(std::vector<priv::Penumbra>& penumbras, std::vector<int>& innerBoundaryIndices, std::vector<sf::Vector2f>& innerBoundaryVectors, std::vector<int>& outerBoundaryIndices, std::vector<sf::Vector2f>& outerBoundaryVectors, const LightShape& shape);

	private:
		sf::RectangleShape mShape; ///< The shape to apply light color

		sf::Vector2f mCastDirection; ///< The cast direction
		float mCastAngle; ///< The cast angle

		float mSourceRadius; ///< The source radius
		float mSourceDistance; ///< The source distance
};

} // namespace ltbl