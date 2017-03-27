/* Sprite.h - Part of the YOLConsoleEngine - v1.0 - HaselLoyance - public domain.
No warranty implied; use at your own risk

TODO header's header (sprite description lmao)
TODO Crop() (which crops the sprite itself) and Subcrop() (which returns the cropped sprite of the current sprite)

SPRITE BINARY FILE FORMAT
--First byte - width in range 0-255 (0x00-0xFF)

--Second byte - height in range 0-255 (0x00-0xFF)

Each sprite pixel is usually 3 bytes:
--First byte - two colors combined such as: byte = firstColor*16+secondColor
	Can be easily retrieved as firstColor(byte/16), secondColor(byte%16)

--Second and third bytes represent UTF16 with big endian encoding 2-byte symbol (wchar_t), such as:
	symbolVal = thirdByte * 256 + fourthByte;

NOTE: Pixel considered empty or transparent when either of two colors is equal to 0xFF (cTransparent)
	Empty pixels take up only one byte and stored as 0x10 value (thus 2 bytes for symbol are just ignored)

LICENSE
This software is dual-licensed to the public domain and under the following
license: you are granted a perpetual, irrevocable license to copy, modify,
publish, and distribute this file as you see fit.
*/


#ifndef YOL_CONSOLE_ENGINE_SPRITE_H
#define YOL_CONSOLE_ENGINE_SPRITE_H

//Global include for all YOLConsoleEngine modules
#include "../include/YOLConsoleEngineMain.h"

namespace YOLConsoleEngine
{
	//Holds all the data about sprite
	//Allows to edit the contents of the sprite
	//2D vectors of foreground color, background color and character of the pixels
	struct __SpriteData
	{
		__SpriteData()
		{
			foregroundColor.resize(0, std::vector<__ConsoleColor>(0, cTransparent));
			backgroundColor.resize(0, std::vector<__ConsoleColor>(0, cTransparent));
			character.resize(0, std::vector<wchar_t>(0, 0xFF));
		}

		//2D vector that stores information about foreground color of the pixel
		std::vector<std::vector<__ConsoleColor>> foregroundColor;

		//2D vector that stores information about background color of the pixel
		std::vector<std::vector<__ConsoleColor>> backgroundColor;

		//2D vector that stores information about character of the pixel
		std::vector<std::vector<wchar_t>> character;
	};


	///////////////////
	//
	//Sprite class
	//
	///////////////////
	class YOL_ENGINE_API __Sprite
	{
	public:
		//Creates sprite file for debug purposes
		void debug_create();

		//Constructor without sprite load
		__Sprite(const std::shared_ptr<__Project> & pr);

		//Constructor with sprite load
		__Sprite(const std::shared_ptr<__Project> & pr, const __Location & loc);

		~__Sprite();

		//Loads all sprite data into 2D arrays
		//Also resets all previously set variables
		__EngineErrors Load(const __Location & loc);

		//Draws the sprite in the specified position
		//If drawAlpha is set to true - transparent pixels of the sprite
		//will be drawn as following: cBlack foreground, cDarkGray background, 'x' character
		void Draw(const __Vec2 & pos, bool drawAlpha = false);

		//Returns sprite file location
		inline __Location GetLocation() { return location; }

		//Returns sprite size
		inline __Size2 GetSize() { return size; }

		//Flips sprite horizontally
		void FlipHorizontally();

		//Flips sprite vertically
		void FlipVertically();

		//Upscales sprite
		void Upscale(int scale);

		//Downscales sprite
		void Downscale(int scale);

		//Inverts sprite colors
		void InvertColors();

		//Transforms sprite colors to grayscale (black and white)
		void ToGrayScale();

		//UNUSED
		//__AnchorPoint anchorPoint;
		//__Rotation Rotation;
		//Rotates the spright CW
		//void RotateRight();
		//Rotates the spright CCW
		//void RotateLeft();
		//Rotates the sprite with angle value
		//void Rotate(double angle);
		//Rotates the sprite with __Direction value
		//void Rotate(__Rotation::__Direction direction);
		//inline void Crop(__Vec2 pos, __Size2 size) { Crop(pos.x, pos.y, size.Width(), size.Height()); }
		//void Crop(double posX, double posY, unsigned int width, unsigned int height);


		//Name of the sprite. No actual purpose
		std::wstring name;

		//Holds all the data about sprite
		__SpriteData data;
		
	private:
		//Initializes all variables
		void Init();


		//Reference to the __Project object
		std::shared_ptr<__Project> project;

		//Paths to the sprite file
		__Location location;

		//Sprite width/height
		__Size2 size;
	};
}

#endif