#include "miniRT.h"
#include "render.h"

void	ambient_computation(t_ambient *amb)
{
	amb->color.r *= amb->ratio;
	amb->color.g *= amb->ratio;
	amb->color.b *= amb->ratio;
}
