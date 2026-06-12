#pragma once
#include <magnetar/magnetar.h>

namespace R
{
	namespace meshes
	{
		magnetar::AssetHandle cube = 1003;
		magnetar::AssetHandle square = 1004;
	}

	namespace textures
	{
		magnetar::AssetHandle wall = 1002;
	}

	namespace shaders
	{
		magnetar::AssetHandle GL_color = 1005;
		magnetar::AssetHandle GL_texture = 1006;
	}

	namespace materials
	{
		magnetar::AssetHandle wall = 1000;
		magnetar::AssetHandle blue = 1001;
	}

}