/** 
 * @file
 * @brief Class @ref ASGE::OGLGame
 */

#pragma once
#include <Engine/Game.h>

namespace ASGE {
	/**
	*  @brief an OpenGL implementation of the Game engine.
	*  
	*  Supporting modern OpenGL this class allows the update and
	*  rendering of game objects, sprites and textures. It makes 
	*  use of simple shaders and manages the creation and destruction
	*  of the OpenGL window subsystem. Currently it does not support
	*  resizing of windows on the fly, or focus loss. 
	*/
	class OGLGame: public Game
	{
	public:
		
		~OGLGame() override = default;

		/**
		* Initialises the OpenGL subsystem.
		* @return True if successful.
		*/
		bool initAPI(Renderer::WindowMode mode =
			Renderer::WindowMode::WINDOWED) final;
		
		/**
		* Terminates the OpenGL subsystem.
		* @return True if managed gracefully.
		*/
		bool exitAPI() noexcept final;
		
		/**
		* Prepares the OpenGL subsystem for the next frame.
		*/
		void beginFrame() final;
		
		/**
		* Clean-up the OpenGL subsystem at the end of the frame.
		* This also includes the updating and rendering of FPS,
		* dynamic_batch rendering, queue management and swapping of
		* buffers. 
		*/
		void endFrame() final;
	};
}